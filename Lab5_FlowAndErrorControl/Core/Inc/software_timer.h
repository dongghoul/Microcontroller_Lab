/*
 * software_timer.h
 *
 *  Created on: Dec 25, 2022
 *      Author: Admin
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TICK 10
#define REQUEST_TIMEOUT_DURATION 3000

extern int timerRequest_flag;

void setTimerRequest(int duration);

void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */