/*
 * Copyright (c) 2020, Lucerne University of Applied Sciences and Arts.
 * @author Lucien Zuercher <lucien.zuercher@stud.hslu.ch>
 */

/**
 * @brief   Application entry for tutorial solution.
 */
#define TUTORIAL_TITLE   "Tutorial 14 LineSensor"
//#define _SOLUTION

#include <stdio.h>

#include "platform.h"
#include "clock_config.h"
#include "peripherals.h"
#include "pin_mux.h"

#include "term.h"
#include "uart.h"

#include "ftm0.h"
#include "sound.h"
#include "sound_player.h"
#include "ir.h"

#include "quad.h"
#include "motor.h"
#include "drive.h"
#include "pwrSwitch.h"
#include "ftm3.h"

#include "i2c.h"
#include "eeprom.h"

#include "colSens.h"
#include "color.h"
#include "joystick.h"
#include "led.h"
#include "adc.h"
#include "SSD1306.h"
#include "linesens.h"

#include "util.h"

// calulate nr of TOF count for a given number of milliseconds
#define TOFS_MS(x)   ((uint16_t)(((FTM3_CLOCK / 1000) * x) / (FTM3_MODULO + 1)))

int16_t speedL = 0;
int16_t speedR = 0;

uint8_t ki = 20, kp = 70;

void ProcessInfraredCommand(char key) {
	uint8_t value = 10;

	switch (key) {
	// motor.c test for left motor
	case Key1:
		motorIncrementPwmLeft(-value);
		break;
	case Key2:
		motorSetPwmLeft(0);
		break;
	case Key3:
		motorIncrementPwmLeft(+value);
		break;

		// motor.c test for right motor
	case Key4:
		motorIncrementPwmRight(-value);
		break;
	case Key5:
		motorSetPwmRight(0);
		break;
	case Key6:
		motorIncrementPwmRight(+value);
		break;

		// drive.c test
	case KeyUp:               // drive forward
		speedL += 100;
		speedR += 100;
		break;

	case KeyDown:             // drive backward
		speedL -= 100;
		speedR -= 100;
		break;

	case KeyRight:            // drive right
		speedR -= 10;
		speedL += 10;
		break;

	case KeyLeft:             // drive left
		speedR += 10;
		speedL -= 10;
		break;

	case KeyOK:               // Stop
		speedR = speedL = 0;
		break;

	case KeyStar:             // predefined velocity
		speedR = speedL = 1300;
		break;
	}

	if (pwr_switch_enabled()) {
		driveSetSpeed(speedL, speedR);
		driveSetParameters(kp, kp, ki, ki);
	} else {

	}
}

void CheckAdc(void) {
	static uint16_t j;

	if (j++ == TOFS_MS(250)) {            // toogle rear leds every 250ms
		j = 0;
		if (adcGet16BitValue(18) > 65000) {
			GPIOA->PTOR = (1 << 17);
			if (adcGetVoltage(18) > 1190000)
				GPIOA->PTOR = (1 << 15);
		}
	}
}

void ProcessDrive(void) {
	static uint16_t i;
	if (i++ == TOFS_MS(PID_PERIOD)) {     // run pid worker every 25ms
		i = 0;
		if (pwr_switch_enabled()) {
			driveToWork();
		} else {
			driveSetSpeed(0, 0);
		}
	}
}

void ProcessColorSensor(void) {
	static uint16_t k;

	if (k++ == TOFS_MS(50)) {
		k = 0;
		tColorRGB col;
		tColorHSV hsv;
		colSensReadColor(&col);
		colorRGBtoHSV(&col, &hsv);
		colorHueToRGB(hsv.hue, &col);
		led_set_color_left(col.red, col.green, col.blue);
		led_set_color_right(col.red, col.green, col.blue);
	}
}

void ProcessJoystick(void) {
	if (joystick() & jsLeft) // Joystick Left Key
			{
		colSensSetBlack();
	}

	if (joystick() & jsRight) // Joystick Right Key
			{
		colSensSetWhite();
	}
}

void UpdateDisplay(void) {
	static uint16_t current;
	char buf[32];
	static uint16_t i;
	if (i++ == TOFS_MS(250)) {
		i = 0;
		int16_t voltage = adcGetBatVoltage();
		current = ((1 * current) + adcGetCurrent()) / 2;
		int16_t temp = adcGetTemperature();
		SSD1306_SetPageStartAddr(0);
		SSD1306_SetColStartAddr(0);

		if (voltage > 0) {
			SSD1306_PrintString("Bat Voltage: ");
			buf[0] = '\0';
			utilStrcatNum16u(buf, sizeof(buf), voltage);
			SSD1306_PrintString(buf);
			SSD1306_PrintString(" mV \n");
		}

		if (current < 5000) {
			SSD1306_PrintString("Current: ");
			buf[0] = '\0';
			utilStrcatNum16u(buf, sizeof(buf), current);
			SSD1306_PrintString(buf);
			SSD1306_PrintString(" mA \n");
		}

		if (temp < 1000) {
			SSD1306_PrintString("Temperature: ");
			buf[0] = '\0';
			utilStrcatNum16s(buf, sizeof(buf), temp / 10);
			utilStrcat(buf, sizeof(buf), ".");
			if (temp < 0)
				temp = -temp;
			utilStrcatNum16s(buf, sizeof(buf), temp % 10);
			SSD1306_PrintString(buf);
			SSD1306_PrintString(" C \n");
		}

		uint8_t s = lsGetSensData();
		uint8_t i;
		SSD1306_PrintString("LS: ");
		for (i = 0; i < 8; i++) {
			if (s & (1 << i)) {
				SSD1306_PrintChar('X');
			} else {
				SSD1306_PrintChar('_');
			}
		}

		SSD1306_PrintChar(' ');
		int8_t dir = lsGetDir();
		buf[0] = '\0';
		utilStrcatNum16s(buf, sizeof(buf), (int16_t) dir);
		SSD1306_PrintString(buf);
		SSD1306_PrintString("   ");

	}
}

/*
 * @brief   Application entry point.
 */
int main(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	// initialize components
	// communication
	ftm0_init(); // FTM0
	ftm3_init(); // ftm3 for motor
	term_init(); // init terminal
	sound_init(); // buzzer
	sound_player_init(); // player
	ir_init(); // infrared

	// driving
	motor_init(); // engine
	quad_init(); // quadrature signal decoder
	drive_init(); // driver variables
	pwr_switch_init(); // power switch
	EnableDebugLeds();
	led_init();

	// peripherals (i2c / display / color sensor)
	i2cInit();
	eepromInit();
	colSensInit();
	joystick_init();
	adc_init();
	lsInit(); // line sensor
	SSD1306_Init();

	// first beep
	sound_beep(4000, 100);

	SSD1306_Clear();

	// print over UART
	utils_print_tutorial(TUTORIAL_TITLE);

	// configure read red leds on PTA15 and PTA17
	PORTA->PCR[15] = PORTA->PCR[17] = PORT_PCR_MUX(1);
	GPIOA->PDDR |= (1 << 15) | (1 << 17) | (1 << 16);

	while (TRUE) {
		// check for commands from terminal
		term_do_work();

		// check for infrared remote control
		char key = ir_get_key();
		if (key)
			ProcessInfraredCommand(key);

		// check for timer overflow
		if (FTM3->SC & FTM_SC_TOF_MASK) {
			FTM3->SC &= ~FTM_SC_TOF_MASK;    // clear TOF flag
			ProcessDrive();
			CheckAdc();
			ProcessColorSensor();
			ProcessJoystick();
			UpdateDisplay();
		}
	}
}
