/*
 * global.h
 *
 *  Created on: Dec 24, 2022
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"

#define MAX_BUFFER_SIZE 30
extern uint8_t buffer [ MAX_BUFFER_SIZE ];

extern int uart_communication_status;
extern int command_parser_status;
extern int request;
extern int ok;

#define INPUT_INIT 11
#define INPUT_STATUS_1 12
#define INPUT_STATUS_2 13
#define INPUT_STATUS_3 14
#define INPUT_STATUS_4 15
#define INPUT_STATUS_5 16
#define INPUT_STATUS_6 17

#define UART_INIT 21
#define UART_REQUEST 22
#define UART_OK 23

#endif /* INC_GLOBAL_H_ */