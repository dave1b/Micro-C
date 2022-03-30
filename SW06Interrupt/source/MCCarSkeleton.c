/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MCCarSkeleton.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	printf("Hello World\n");

	CLOCK_EnableClock(kCLOCK_PortD);

	NVIC_SetPriority(PORTB_IRQn, 8); // Set interrupt priority: 0..15, 0 = max. Priority
	NVIC_EnableIRQ(PORTB_IRQn);      // enable interrupt
	// NVIC_DisableIRQ(PORTB_IRQn);  // disable interrupt

	while (1) {
		printLEDcounter();
		SDK_DelayAtLeastUs(5000000, CLOCK_GetCoreSysClkFreq());
	}
	return 0;
}

struct ledCounter {
	unsigned short frontRightRed;
	unsigned short frontRightGreen;
	unsigned short frontRightBlue;
	unsigned short frontRightYellow;
	unsigned short frontRightPurple;

	unsigned short frontLeftRed;
	unsigned short frontLeftGreen;
	unsigned short frontLeftBlue;
	unsigned short frontLeftYellow;
	unsigned short frontLeftPurple;

	unsigned short rearRightRed;
	unsigned short rearLeftRed;
};

struct ledCounter ledC = { 0, 0, 0, 0, 0, 0, 0, 0 };

void printLEDcounter() {
	printf(
			"frontRightRed: %d, frontRightGreen: %d,frontRightBlue: %d, frontRightYelow: %d, frontRightPurple: %d,frontLeftRed: "
					"%d, frontLeftGreen: %d, frontLeftBlue: %d, frontLeftYellow: %d, frontLeftPurple: %d,rearRightRed: %d, rearLeftRed: %d\n",
			ledC.frontRightRed, ledC.frontRightGreen, ledC.frontRightBlue,
			ledC.frontRightYellow, ledC.frontRightPurple, ledC.frontLeftRed,
			ledC.frontLeftGreen, ledC.frontLeftBlue, ledC.frontLeftYellow,
			ledC.frontLeftPurple, ledC.rearRightRed, ledC.rearLeftRed);
}

unsigned short colorCode[] = { 0, 1, 2, 3, 4 }; // red, green, blue, yellow, purple
unsigned short frontRightLEDColor = 0;
unsigned short frontLeftLEDColor = 0;
bool frontLEDon = 0;

void turnFrontRightLEDon() {
	switch (frontRightLEDColor) {
	case 0:
		GPIO_PinWrite(GPIOD, 2, 0);  // front right  red
		ledC.frontRightRed++;
		break;
	case 1:
		GPIO_PinWrite(GPIOC, 11, 0); // front right  green
		ledC.frontRightGreen++;
		break;
	case 2:
		GPIO_PinWrite(GPIOD, 3, 0);  // front right blue
		ledC.frontRightBlue++;
		break;
	case 3:
		GPIO_PinWrite(GPIOC, 11, 0); // front right  green   --> yellow
		GPIO_PinWrite(GPIOD, 3, 0);  // front right blue
		ledC.frontRightYellow++;
		break;
	case 4:
		GPIO_PinWrite(GPIOD, 2, 0);  // front right  red     --> purple
		GPIO_PinWrite(GPIOD, 3, 0);  // front right blue
		ledC.frontRightPurple++;
		break;
	}
}
void turnFrontLeftLEDon() {
	switch (frontLeftLEDColor) {
	case 0:
		GPIO_PinWrite(GPIOC, 9, 0);  // front left  red
		ledC.frontLeftRed++;
		break;
	case 1:
		GPIO_PinWrite(GPIOC, 8, 0);  // front left  green
		ledC.frontLeftGreen++;
		break;
	case 2:
		GPIO_PinWrite(GPIOC, 10, 0); // front left blue
		ledC.frontLeftBlue++;
		break;
	case 3:
		GPIO_PinWrite(GPIOC, 8, 0);  // front left  green   --> yellow
		GPIO_PinWrite(GPIOC, 10, 0); // front left blue
		ledC.frontLeftYellow++;
		break;
	case 4:
		GPIO_PinWrite(GPIOC, 9, 0);  // front left  red     --> purple
		GPIO_PinWrite(GPIOC, 10, 0); // front left blue
		ledC.frontLeftPurple++;
		break;
	}
}

void turnFrontLEDsOn() {
	if(frontLEDon){
	turnFrontLEDsOff();
	turnFrontRightLEDon();
	turnFrontLeftLEDon();
	}
}

void turnBackLEDsOn() {
	GPIO_PinWrite(GPIOA, 15, 0); // rear  right  red
	GPIO_PinWrite(GPIOA, 17, 0); // rear  left   red
}

void turnFrontLEDsOff() {
	GPIO_PinWrite(GPIOD, 2, 1);  // front right  red
	GPIO_PinWrite(GPIOC, 8, 1);  // front left   green
	GPIO_PinWrite(GPIOD, 3, 1);  // front right  blue
	GPIO_PinWrite(GPIOC, 9, 1);  // front left   red
	GPIO_PinWrite(GPIOC, 10, 1); // front left   blue // GPIO_PinWrite(LED_BLUE_F_L_GPIO LED_BLUE_F_L_PIN,1)
	GPIO_PinWrite(GPIOC, 11, 1); // front right  green
}

void turnAllLEDsOff() {
	GPIO_PinWrite(GPIOD, 2, 1);  // front right  red
	GPIO_PinWrite(GPIOC, 8, 1);  // front left   green
	GPIO_PinWrite(GPIOD, 3, 1);  // front right  blue
	GPIO_PinWrite(GPIOC, 9, 1);  // front left   red
	GPIO_PinWrite(GPIOC, 10, 1); // front left   blue // GPIO_PinWrite(LED_BLUE_F_L_GPIO LED_BLUE_F_L_PIN,1)
	GPIO_PinWrite(GPIOC, 11, 1); // front right  green
	GPIO_PinWrite(GPIOA, 15, 1); // rare  right  red
	GPIO_PinWrite(GPIOA, 17, 1); // rare  left   red
}

/* PORT_GetPinsInterruptFlags
 * 1 = right
 * 512 = left
 * 8 = push
 * 4 = up
 * 2 = down
 */
void PORTB_IRQHandler(void) {
	uint32_t pin = PORT_GetPinsInterruptFlags(PORTB);
	//printf("IRQ Detected at pin: %d \n", pin);
	switch (pin) {
	case 1:
		frontRightLEDColor = (frontRightLEDColor + 1) % 5;
		turnFrontLEDsOn();
		break;
	case 512:
		frontLeftLEDColor = (frontLeftLEDColor + 1) % 5;
		turnFrontLEDsOn();
		break;
	case 8:
		frontLEDon = 0;
		turnAllLEDsOff();
		break;
	case 4:
		frontLEDon = 1;
		turnFrontLEDsOn();
		break;
	case 2:
		turnBackLEDsOn();
		break;
	}
	PORT_ClearPinsInterruptFlags(PORTB, (1 << 3));
	PORT_ClearPinsInterruptFlags(PORTB, (1 << 2));
	PORT_ClearPinsInterruptFlags(PORTB, (1 << 1));
	PORT_ClearPinsInterruptFlags(PORTB, (1 << 0));
	PORT_ClearPinsInterruptFlags(PORTB, (1 << 9));
}
