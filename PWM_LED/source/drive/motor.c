/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         motor driver
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          15.04.2020
 *
 *--------------------------------------------------------------------
 */

#include "platform.h"
#include "motor.h"
#include "ftm3.h"
#include "term.h"
#include "util.h"
#include <string.h>
#if !SOLUTION

// https://ebldc.com/?p=86

// todo #09.04 complete the macros to switch a pin configuration from GPIO to FTM-Mode and vice versa
#define MOTOR_RIGHT_A_PWM()           (PORTD->PCR[0] = PORT_PCR_MUX(4))  // PTD0[4]: FTM3_CH0
#define MOTOR_RIGHT_A_GPIO()          (PORTD->PCR[0] = PORT_PCR_MUX(1))  // PTD0[1]: GPIO
#define MOTOR_RIGHT_B_PWM()           (PORTE->PCR[5] = PORT_PCR_MUX(6))  // PTE5[6]: FTM3_CH0
#define MOTOR_RIGHT_B_GPIO()          (PORTE->PCR[5] = PORT_PCR_MUX(1))  // PTE5[1]: GPIO

#define MOTOR_LEFT_A_PWM()            (PORTD->PCR[1] = PORT_PCR_MUX(4))  // PTD1[4]: FTM3_CH0
#define MOTOR_LEFT_A_GPIO()           (PORTD->PCR[1] = PORT_PCR_MUX(1))  // PTD1[1]: GPIO
#define MOTOR_LEFT_B_PWM()            (PORTE->PCR[6] = PORT_PCR_MUX(6))  // PTE6[6]: FTM3_CH0
#define MOTOR_LEFT_B_GPIO()           (PORTE->PCR[6] = PORT_PCR_MUX(1))  // PTE6[1]: GPIO

static tCommandLineHandler clh;       // terminal command line handler
static int8_t valueRight;
static int8_t valueLeft;



/**
 * Increments or decrements the PWM value oft the right wheel
 * @param[in] value
 *   a positive or negative value to add
 */
void motorIncrementPwmRight(int8_t value)
{
  int32_t v = valueRight + value;
  if (v > MOTOR_MAX_VALUE) v = MOTOR_MAX_VALUE;
  if (v < -MOTOR_MAX_VALUE) v = -MOTOR_MAX_VALUE;
  motorSetPwmRight((int8_t)v);
}


/**
 * Increments or decrements the PWM value oft the left wheel
 * @param[in] value
 *   a positive or negative value to add
 */
void motorIncrementPwmLeft(int8_t value)
{
  int32_t v = valueLeft + value;
  if (v > MOTOR_MAX_VALUE) v = MOTOR_MAX_VALUE;
  if (v < -MOTOR_MAX_VALUE) v = -MOTOR_MAX_VALUE;
  motorSetPwmLeft((int8_t)v);
}


/**
 * Sets the PWM value of the right wheel
 *
 * @param[in] value
 *   the value between -MOTOR_MAX_VALUE..0..+MOTOR_MAX_VALUE
 *   A value of '0' stops the wheel.
 */
void motorSetPwmRight(int8_t value)
{
  if (value > MOTOR_MAX_VALUE) value = MOTOR_MAX_VALUE;
  if (value < -MOTOR_MAX_VALUE) value = -MOTOR_MAX_VALUE;
  valueRight = value;

  if (value < 0)
  {
    // drive backward
    value = -value;             // value has to be a positive channel value!
    MOTOR_RIGHT_A_GPIO();       // set motor right A as GPIO Pin (high-level)
    MOTOR_RIGHT_B_PWM();        // set motor right B as timer Pin (pwm signal)
  }
  else if (value > 0)
  {
    // drive forward
    // todo #09.08 complete the else-if statemen
	MOTOR_RIGHT_A_PWM();        // set motor right A as timer Pin (pwm signal)
   	MOTOR_RIGHT_B_GPIO();       // set motor right B as GPIO Pin (high-level)
  }
  else
  {
    // stop
    // todo #09.09 complete the else statement
	  MOTOR_RIGHT_A_GPIO();       // set motor right A as GPIO Pin (high-level)
	  MOTOR_RIGHT_B_GPIO();       // set motor right B as GPIO Pin (high-level)
  }
  int16_t v = (uint16_t)(((FTM3_MODULO + 1) * ((uint32_t)value)) / MOTOR_MAX_VALUE);
  FTM3->CONTROLS[0].CnV = v;
}


/**
 * Sets the PWM value of the left wheel
 *
 * @param[in] value
 *   the value between -MOTOR_MAX_VALUE..0..+MOTOR_MAX_VALUE
 *   A value of '0' stops the wheel.
 */
void motorSetPwmLeft(int8_t value)
{
  // todo #09.10 complete the function as above
	if (value > MOTOR_MAX_VALUE) value = MOTOR_MAX_VALUE;
	if (value < -MOTOR_MAX_VALUE) value = -MOTOR_MAX_VALUE;
	valueLeft = value;

	  if (value < 0)
	  {
	    // drive backward
	    value = -value;             // value has to be a positive channel value!
	    MOTOR_LEFT_A_PWM();        // set motor right A as timer Pin (pwm signal)
		 MOTOR_LEFT_B_GPIO();       // set motor right B as GPIO Pin (high-level)
	  }
	  else if (value > 0)
	  {
	    // drive forward
		MOTOR_LEFT_A_GPIO();       // set motor right A as GPIO Pin (high-level)
		MOTOR_LEFT_B_PWM();        // set motor right B as timer Pin (pwm signal)

	  }
	  else
	  {
	    // stop
		  MOTOR_LEFT_A_GPIO();       // set motor right A as GPIO Pin (high-level)
		  MOTOR_LEFT_B_GPIO();       // set motor right B as GPIO Pin (high-level)
	  }
	  int16_t v = (uint16_t)(((FTM3_MODULO + 1) * ((uint32_t)value)) / MOTOR_MAX_VALUE);
	  FTM3->CONTROLS[1].CnV = v;
}


/**
 * Command line parser for this file.
 * This code is complete and works.
 *
 * @param[in] cmd
 *   the command to parse
 */
tError motorParseCommand(const char *cmd)
{
  tError result = EC_INVALID_ARG;
  if (strcmp(cmd, "help") == 0)
  {
    termWriteLine("mot (motor) commands:");
    termWriteLine("  help");
    termWriteLine("  setL [-100..100]");
    termWriteLine("  setR [-100..100]");
    termWriteLine("  status");
    result = EC_SUCCESS;
  }
  else if (strncmp(cmd, "setL", sizeof("setL")-1) == 0)
  {
    cmd += sizeof("setL");
    int16_t v;
    result = utilScanDecimal16s(&cmd, &v);
    if (result != EC_SUCCESS) return result;
    motorSetPwmLeft((int16_t)((MOTOR_MAX_VALUE * v) / 100));
  }
  else if (strncmp(cmd, "setR", sizeof("setR")-1) == 0)
  {
    cmd += sizeof("setR");
    int16_t v;
    result = utilScanDecimal16s(&cmd, &v);
    if (result != EC_SUCCESS) return result;
    motorSetPwmRight((int16_t)((MOTOR_MAX_VALUE * v) / 100));
  }
  return result;
}



/**
 * Initializes the motor driver:
 * - Motor R A: PTD0, FTM3_CH0, Mux:4
 * - Motor R B: PTE5, FTM3_CH0, Mux:6
 * - Motor L A: PTD1, FTM3_CH1, Mux:4
 * - motor L B: PTE6, FTM3_CH1, Mux:6
 */
void motorInit(void)
{
  // todo #09.05 Configure the pin direction of the 4 pins as output.
	//GPIOD->PDDR |=	GPIO_PDDR_PDD(0) | GPIO_PDDR_PDD(1);
	//GPIOE->PDDR |=	GPIO_PDDR_PDD(5) | GPIO_PDDR_PDD(6);
	GPIOD->PDDR |= 3; 		// 11
	GPIOE->PDDR |= 0x60;	//110000

  // todo #09.06 set the pin value of all of the 4 pins to '1'
	//GPIOD->PDOR |=	GPIO_PDOR_PDO(0) | GPIO_PDOR_PDO(1);
	//GPIOE->PDOR |=	GPIO_PDOR_PDO(5) | GPIO_PDOR_PDO(6);
	GPIOD->PDOR |= 3;
	GPIOE->PDOR |= 0x60;

  // configures the pin muxing of all of the 4 pins as GPIO-Pin.
  // the output level will be '1' because of the configuration above.
  MOTOR_LEFT_A_GPIO();
  MOTOR_LEFT_B_GPIO();
  MOTOR_RIGHT_A_GPIO();
  MOTOR_RIGHT_B_GPIO();

  // todo #09.07 configure both channels as edge aligned PWM with low-true pulses
  FTM3->CONTROLS[0].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSA(1);
  FTM3->CONTROLS[1].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSA(1);

  // register terminal command line handler
  termRegisterCommandLineHandler(&clh, "mot", "(motor)", motorParseCommand);
}
#endif
