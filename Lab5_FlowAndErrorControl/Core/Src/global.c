/*
 * global.c
 *
 *  Created on: Dec 24, 2022
 *      Author: Admin
 */

#include "global.h"

int uart_communication_status = 21;
int command_parser_status = 11;

int request;
int ok;

uint8_t buffer [ MAX_BUFFER_SIZE ];
