/*
 * input_processing.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Admin
 */
#include "input_processing.h"

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED} ;
enum ButtonState button1State = BUTTON_PRESSED;
enum ButtonState button2State = BUTTON_PRESSED;
enum ButtonState button3State = BUTTON_PRESSED;

void fsm_for_button1_processing(void){
	switch(button1State){
	case BUTTON_RELEASED:
		if(is_button_pressed(0)){
			button1State = BUTTON_PRESSED;
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
		break;
	case BUTTON_PRESSED:
		if(!is_button_pressed(0)){
			button1State = BUTTON_RELEASED;
		}
		break;
	}
}

void fsm_for_button2_processing(void){
	switch(button2State){
	case BUTTON_RELEASED:
		if(is_button_pressed(1)){
			button2State = BUTTON_PRESSED;
			if (MODE != AUTOMATIC){
				newTimer++;
				if (newTimer >= 100)
					newTimer = 1;
				updateClockBuffer(newTimer, MODE);
			}
		}
		break;
	case BUTTON_PRESSED:
		if(!is_button_pressed(1)){
			button2State = BUTTON_RELEASED;
		}
		break;
	}
}

void fsm_for_button3_processing(void){
	switch(button3State){
	case BUTTON_RELEASED:
		if(is_button_pressed(2)){
			button3State = BUTTON_PRESSED;
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
	case BUTTON_PRESSED:
		if(!is_button_pressed(2)){
			button3State = BUTTON_RELEASED;
		}
		break;
	}
}

