/*
 * uart_communication_fsm.c
 *
 *  Created on: Dec 24, 2022
 *      Author: Admin
 */
#include "uart_communication_fsm.h"

uint32_t ADC_value = 50;
char str[50];

void get_ADC_value()
{
	ADC_value = HAL_ADC_GetValue(&hadc1);
}

void send_output()
{
	HAL_UART_Transmit(&huart2, (void*)str , sprintf(str, "!ADC=%4d\n", ADC_value), 1000);
}

void uart_communication_fsm()
{
	switch (uart_communication_status){
	case UART_INIT:
		if (request == 1){
			uart_communication_status = UART_REQUEST;
			setTimerRequest(REQUEST_TIMEOUT_DURATION);
			get_ADC_value();
			send_output();
			request = 0;
		}
		break;
	case UART_REQUEST:
		if (request == 1){
			setTimerRequest(REQUEST_TIMEOUT_DURATION);
			get_ADC_value();
			send_output();
			request = 0;
		}
		else if (ok == 1){
			uart_communication_status = UART_INIT;
			ok = 0;
		}
		else if (timerRequest_flag == 1){
			uart_communication_status = UART_INIT;
			send_output();
		}
		break;
	}
}
