/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 24, 2022
 *      Author: Admin
 */
#include "command_parser_fsm.h"

int index = 0;

void command_parser_fsm()
{
	uint8_t input = buffer[index];
	switch (command_parser_status){
	case INPUT_INIT:
		if ( input == ('!'))
			command_parser_status = INPUT_STATUS_1;
		else
			command_parser_status = INPUT_INIT;
		break;
	case INPUT_STATUS_1:
		if (input == ('R'))
			command_parser_status = INPUT_STATUS_2;
		else if (input == ('O'))
			command_parser_status = INPUT_STATUS_5;
		else
			command_parser_status = INPUT_INIT;
		break;
	case INPUT_STATUS_2:
		if (input== ('S'))
			command_parser_status = INPUT_STATUS_3;
		else
			command_parser_status = INPUT_INIT;
		break;
	case INPUT_STATUS_3:
		if (input == ('T'))
			command_parser_status = INPUT_STATUS_4;
		else
			command_parser_status = INPUT_INIT;
		break;
	case INPUT_STATUS_4:
		if (input == ('#')){
			request = 1;
			ok = 0;
			command_parser_status = INPUT_INIT;
		}
		else
			command_parser_status = INPUT_INIT;
		break;
	case INPUT_STATUS_5:
		if (input == ('K'))
			command_parser_status = INPUT_STATUS_6;
		else
			command_parser_status = INPUT_INIT;
		break;
	case INPUT_STATUS_6:
		if (input == ('#')){
			ok = 1;
			command_parser_status = INPUT_INIT;
		}
		else
			command_parser_status = INPUT_INIT;
		break;
	default:
		break;
	}
	index++;
	if (index >= MAX_BUFFER_SIZE)
		index = 0;
}
