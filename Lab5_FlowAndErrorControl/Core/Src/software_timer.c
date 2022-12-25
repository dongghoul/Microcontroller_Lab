/*
 * software_timer.c
 *
 *  Created on: Dec 25, 2022
 *      Author: Admin
 */

#include "software_timer.h"

int timerRequest_counter = 0;
int timerRequest_flag = 0;

void setTimerRequest(int duration){
	timerRequest_counter = duration / TICK;
	timerRequest_flag = 0;
}

void timerRun(){
	if(timerRequest_counter > 0){
		timerRequest_counter--;
		if(timerRequest_counter == 0){
			timerRequest_flag = 1;
		}
	}
}