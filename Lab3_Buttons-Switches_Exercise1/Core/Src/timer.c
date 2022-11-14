/*
 * timer.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Admin
 */
#include "timer.h"

#define TIMER_CYCLE 10

int timerClock_flag = 0;
int timerClock_counter = 0;
int timerHorizontalTraffic_flag = 0;
int timerHorizontalTraffic_counter = 0;
int timerHorizontalTraffic = 0;
int timerVerticalTraffic_flag = 0;
int timerVerticalTraffic_counter = 0;
int timerVerticalTraffic = 0;
int timer7seg_counter = 0;
int timer7seg_flag = 0;
int timerBlinking2Hz_flag = 0;
int timerBlinking2Hz_counter = 0;

void setTimerBlinking2Hz(int duration){
	timerBlinking2Hz_flag = 0;
	timerBlinking2Hz_counter = duration /TIMER_CYCLE;
}

void setTimer7seg(int duration){
	timer7seg_flag = 0;
	timer7seg_counter = duration /TIMER_CYCLE;
}

void setTimerClock(int duration){
	timerClock_flag = 0;
	timerClock_counter = duration /TIMER_CYCLE;
}

void setTimerHorizontalTraffic(int duration){
	timerHorizontalTraffic_flag = 0;
	timerHorizontalTraffic_counter = duration /TIMER_CYCLE;
	timerHorizontalTraffic = duration / 1000;
}

void setTimerVerticalTraffic(int duration){
	timerVerticalTraffic_flag = 0;
	timerVerticalTraffic_counter = duration /TIMER_CYCLE;
	timerVerticalTraffic = duration / 1000;
}

void timerRun(){
	if (timerClock_counter > 0){
		timerClock_counter--;
		if (timerClock_counter == 0)
			timerClock_flag = 1;
	}
	if (timerHorizontalTraffic_counter > 0){
		timerHorizontalTraffic_counter--;
		if (timerHorizontalTraffic_counter == 0)
			timerHorizontalTraffic_flag = 1;
	}
	if (timerVerticalTraffic_counter > 0){
		timerVerticalTraffic_counter--;
		if (timerVerticalTraffic_counter == 0)
			timerVerticalTraffic_flag = 1;
	}
	if (timer7seg_counter > 0){
		timer7seg_counter--;
		if (timer7seg_counter == 0)
			timer7seg_flag = 1;
	}
	if (timerBlinking2Hz_counter > 0){
		timerBlinking2Hz_counter--;
		if (timerBlinking2Hz_counter == 0)
			timerBlinking2Hz_flag = 1;
	}
}
