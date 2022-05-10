/*
 * Copyright (c) 2020, Lucerne University of Applied Sciences and Arts.
 * @author Lucien Zuercher <lucien.zuercher@stud.hslu.ch>
 */

/**
 * @brief   Application entry for tutorial solution.
 */
#define TUTORIAL_TITLE   "Tutorial 10 Timer IC"

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

#include "util.h"


/*
 * @brief   Application entry point.
 */
int main(void) {
    /* Init board hardware. */
	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    // initialize components
	ftm0_init(); // FTM0
    term_init(); // init terminal
    sound_init(); // buzzer
    sound_player_init(); // player
    ir_init(); // infrared

    // first beep
    sound_beep(4000, 100);

    // print over UART
    utils_print_tutorial(TUTORIAL_TITLE);

    // main application loop
    while(1) {
		term_do_work();

		char key = ir_get_key();

		if(key != 0) term_write_line_format("Key Received: %c", key);

		if(key == KeyStar) sound_beep(4000, 100);
		if(key == Key1) sound_beep(1000, 100);
		if(key == Key2) sound_beep(2000, 100);
		if(key == Key3) sound_beep(3000, 100);
		if(key == KeyOK) sound_stop();
		if(key == Key4) sound_play_jp();
    }
    return 0 ;
}
