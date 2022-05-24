/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Exercise 09 - Motor Driver with PWM
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          14.04.2020
 *
 *--------------------------------------------------------------------
 */
#include "platform.h"
#include "ftm0.h"
#include "ftm3.h"
#include "motor.h"
#include "quad.h"
#include "ir.h"
#include "term.h"
#include "sound.h"
#include "soundPlayer.h"
#include "drive.h"
#include "pwrSwitch.h"
#include "led.h"
#include "color.h"


#include "platform.h"


#define BrightnessGreen			(0xEF00) //(0xFFB6) (61184)10
#define BrightnessRed			(0x0FFF) //(0xCF65) (4095)10
#define BrightnessBlue			(0x2EE0) //(0xCF65) (12000)10

void main(void) {

	SIM->SCGC6 |= SIM_SCGC6_FTM3_MASK;           	// set clockgating FTM3 -> ftm3-timer wird hier eingeschaltet
	FTM3->SC = FTM_SC_CLKS(1) | FTM_SC_PS(4); 		// set clocksource to "system clock" = 75Hz, PS = 16
	FTM3->MOD = 0xFFFF;								// modulo off bzw. auf höchstem Wert

	PORTC->PCR[8] = PORT_PCR_MUX(3);              	// LED green: set port muxing to FTM3 CH4 -> Alt3
	PORTC->PCR[9] = PORT_PCR_MUX(3);				// LED red: set port muxing to FTM3 CH4 -> Alt3
	PORTC->PCR[10] = PORT_PCR_MUX(3);				// LED blue: set port muxing to FTM3 CH4 -> Alt3

	FTM3->CONTROLS[4].CnSC = FTM_CnSC_MSx(2) | FTM_CnSC_ELSx(2) | FTM_CnSC_CHIE(0);//channel interrupt enabler		// Channel Mode: Edge-Aligned PWM, high-true pulses
	FTM3->CONTROLS[5].CnSC = FTM_CnSC_MSx(2) | FTM_CnSC_ELSx(2) | FTM_CnSC_CHIE(0);		// Channel Mode: Edge-Aligned PWM, high-true pulses
	FTM3->CONTROLS[6].CnSC = FTM_CnSC_MSx(2) | FTM_CnSC_ELSx(2) | FTM_CnSC_CHIE(0);		// Channel Mode: Edge-Aligned PWM, high-true pulses
//CnV -> channel value
	FTM3->CONTROLS[4].CnV =  BrightnessGreen;
	FTM3->CONTROLS[5].CnV =  BrightnessRed;
	FTM3->CONTROLS[6].CnV =  BrightnessBlue;

	while (1) {
	}
}
