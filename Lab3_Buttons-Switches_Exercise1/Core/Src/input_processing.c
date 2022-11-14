/*
 * input_processing.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Admin
 */
#include "input_processing.h"

enum ButtonState{BUTTONS_INIT, BUTTONS_RELEASED, BUTTON1_PRESSED, BUTTON2_PRESSED, BUTTON3_PRESSED} ;

enum ButtonState buttonsState = BUTTONS_INIT;

void fsm_for_buttons_processing(void){
	switch (buttonsState){
	case BUTTONS_INIT:
		if(!is_button_pressed(0)){
			buttonsState = BUTTONS_RELEASED;
		}
		break;
	case BUTTONS_RELEASED:
		if(is_button_pressed(0)){
			buttonsState = BUTTON1_PRESSED;
			//INCREASE MODE
			switch (MODE) {
			case AUTOMATIC:
				MODE = MANUAL_RED;
				break;
			case MANUAL_RED:
				MODE = MANUAL_YELLOW;
				break;
			case MANUAL_YELLOW:
				MODE = MANUAL_GREEN;
				break;
			case MANUAL_GREEN:
				MODE = AUTOMATIC;
				initState();
				break;
			}
			//reset newTimer
			newTimer = 1;
			//clear all leds for next mode
			clearAllLeds();
			//update clock buffer if mode is 2, 3, 4
			if (MODE != AUTOMATIC)
				updateClockBuffer(newTimer, MODE);
		}
		else if(is_button_pressed(1)){
			buttonsState = BUTTON2_PRESSED;
			if (MODE != AUTOMATIC){
				newTimer++;
				if (newTimer >= 100)
					newTimer = 1;
				updateClockBuffer(newTimer, MODE);
			}
		}
		else if(is_button_pressed(2)){
			buttonsState = BUTTON3_PRESSED;
			switch (MODE){
			case MANUAL_RED:
				RED_TIME = newTimer * 1000;
				break;
			case MANUAL_YELLOW:
				YELLOW_TIME = newTimer * 1000;
				break;
			case MANUAL_GREEN:
				GREEN_TIME = newTimer * 1000;
				break;
			default:
				break;
			}
		}
		break;
	case BUTTON1_PRESSED:
		if(!is_button_pressed(0)){
			buttonsState = BUTTONS_RELEASED;
		}
		break;
	case BUTTON2_PRESSED:
		if(!is_button_pressed(1)){
			buttonsState = BUTTONS_RELEASED;
		}
		break;
	case BUTTON3_PRESSED:
		if(!is_button_pressed(2)){
			buttonsState = BUTTONS_RELEASED;
		}
		break;
	default:
		break;
	}
}