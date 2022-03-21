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

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

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
//    	PORTD->PCR[3] |= (1<<8);
//    	GPIOD->PDDR |= (1<<3);
//    	GPIOD->PDOR |= (1<<3);


    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */

    void resetLEDs() {
    	GPIO_PinWrite(GPIOD, 2, 1);  // front right  red
    	GPIO_PinWrite(GPIOD, 3, 1);  // front right  blue
    	GPIO_PinWrite(GPIOC, 8, 1);  // front left   green
    	GPIO_PinWrite(GPIOC, 9, 1);  // front left   red
		GPIO_PinWrite(GPIOC, 10, 1); // front left   blue // GPIO_PinWrite(LED_BLUE_F_L_GPIO LED_BLUE_F_L_PIN,1)
        GPIO_PinWrite(GPIOC, 11, 1); // front right  green
		GPIO_PinWrite(GPIOA, 15, 1); // rare  right  red
		GPIO_PinWrite(GPIOA, 17, 1); // rare  left   red
    }


    while (1) {

    	//up green front
    		if(!GPIO_PinRead(GPIOB,2)) {
    			printf("up\n");
    			GPIO_PinWrite(GPIOC, 8, 0); // green f l
    			GPIO_PinWrite(GPIOC, 11, 0); // green f r
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    		}

    	// down red back
    		if(!GPIO_PinRead(GPIOB,1)) {
    			printf("down\n");
    			GPIO_PinWrite(GPIOA, 17, 0); // red b l
    			GPIO_PinWrite(GPIOA, 15, 0); // red b r
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();

    		}


    		if(!GPIO_PinRead(GPIOB,0)) {
    			printf("right\n");
    			GPIO_PinWrite(GPIOD, 2, 0); // front right red
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    			GPIO_PinWrite(GPIOC, 11, 0); // front right green
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    			GPIO_PinWrite(GPIOD, 3, 0); // front right blue
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    			GPIO_PinWrite(GPIOC, 11, 0); //green
    			GPIO_PinWrite(GPIOD, 2, 0); // + red -> front right yellow
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    		}
    		if(!GPIO_PinRead(GPIOB,9)) {
    			printf("left\n");
    			GPIO_PinWrite(GPIOC, 9, 0); // front left red
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    			GPIO_PinWrite(GPIOC, 8, 0); // front left green
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    			GPIO_PinWrite(GPIOC, 10, 0); // front left blue
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    			GPIO_PinWrite(GPIOC, 8, 0); //green
    			GPIO_PinWrite(GPIOC, 9, 0); // + red -> front right yellow
    			SDK_DelayAtLeastUs(500000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    		}
    		if(!GPIO_PinRead(GPIOB,3)) {
    			printf("push\n");
    			int i;
    			for(i=0; i<50; i++) {
    				printf("in for");
    				printf(i);
    			GPIO_PinWrite(GPIOD, 2, 0);  // front right  red
    			GPIO_PinWrite(GPIOC, 9, 0);  // front left   red
    			GPIO_PinWrite(GPIOA, 15, 0); // rare  right  red
    			GPIO_PinWrite(GPIOA, 17, 0); // rare  left   red
    			SDK_DelayAtLeastUs(10000, CLOCK_GetCoreSysClkFreq());
    			resetLEDs();
    			SDK_DelayAtLeastUs(10000, CLOCK_GetCoreSysClkFreq());

    			}
    		}



    	}
    return 0 ;
}
