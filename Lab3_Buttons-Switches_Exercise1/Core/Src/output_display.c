/*
 * output_display.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Admin
 */
#include "output_display.h"

void clearAllLeds(){
	HAL_GPIO_WritePin(GPIOA, HORIZONTAL_RED_Pin|HORIZONTAL_GREEN_Pin|HORIZONTAL_YELLOW_Pin
							|VERTICAL_GREEN_Pin|VERTICAL_RED_Pin|VERTICAL_YELLOW_Pin, GPIO_PIN_RESET);
}

void display7SEG(int num){
	//outputs: SEG7 -> SEG0
	//outputs with value of 0 (RESET) will be turn on
	//outputs with value of 1 (SET) will be turn off
	if (num == 0){ //100 0000
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin
								|SEG3_Pin|SEG4_Pin|SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG6_Pin, GPIO_PIN_SET);
	}
	else if (num == 1){ //111 1001
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG3_Pin|SEG4_Pin
								|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);
	}
	else if (num == 2){ //010 0100
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG3_Pin
								|SEG4_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG2_Pin|SEG5_Pin, GPIO_PIN_SET);
	}
	else if (num == 3){ //011 0000
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin
								|SEG3_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG4_Pin|SEG5_Pin, GPIO_PIN_SET);
	}
	else if (num == 4){ //001 1001
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin|SEG5_Pin
								|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG3_Pin|SEG4_Pin, GPIO_PIN_SET);
	}
	else if (num == 5){ //001 0010
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin
								|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG4_Pin, GPIO_PIN_SET);
	}
	else if (num == 6){ //000 0010
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin
								|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin, GPIO_PIN_SET);
	}
	else if (num == 7){ //111 1000
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG3_Pin|SEG4_Pin|SEG5_Pin
								|SEG6_Pin, GPIO_PIN_SET);
	}
	else if (num == 8){ //000 0000
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin
								|SEG3_Pin|SEG4_Pin|SEG5_Pin
								|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (num == 9){ //001 0000
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin
								|SEG3_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG4_Pin, GPIO_PIN_SET);
	}
}

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};
void update7SEG(int index){
	switch (index){
		case 0:
			//turn on first 7seg led only
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			break;
		case 1:
			//turn on second 7seg led only
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			break;
		case 2:
			//turn on third 7seg led only
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			break;
		case 3:
			//turn on fourth 7seg led only
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
	//display number according to led_buffer and index
	display7SEG(led_buffer[index]);
}

void updateClockBuffer(int first, int second){
	led_buffer[0] = first / 10;
	led_buffer[1] = first % 10;
	led_buffer[2] = second / 10;
	led_buffer[3] = second % 10;
}

void blinkingLed2Hz(GPIO_TypeDef* horizontalPort, uint16_t horizontalPin,
			  	  	GPIO_TypeDef* verticalPort, uint16_t verticalPin)
{
	//blinking coresponding color in 2 Hz
	if (timerBlinking2Hz_flag == 1){
		setTimerBlinking2Hz(250);
		HAL_GPIO_TogglePin(horizontalPort, horizontalPin);
		HAL_GPIO_TogglePin(verticalPort, verticalPin);
	}
}

void output_display(){
	switch (MODE){
	case AUTOMATIC:
		if (timerClock_flag == 1){
			setTimerClock(1000);
			updateClockBuffer(timerHorizontalTraffic, timerVerticalTraffic);
			timerHorizontalTraffic--;
			timerVerticalTraffic--;
		}
		fsm_for_automatic_traffic_light();
		break;
	case MANUAL_RED:
		blinkingLed2Hz(HORIZONTAL_RED_GPIO_Port, HORIZONTAL_RED_Pin,
							   VERTICAL_RED_GPIO_Port, VERTICAL_RED_Pin);
		break;
	case MANUAL_YELLOW:
		blinkingLed2Hz(HORIZONTAL_YELLOW_GPIO_Port, HORIZONTAL_YELLOW_Pin,
					   VERTICAL_YELLOW_GPIO_Port, VERTICAL_YELLOW_Pin);
		break;
	case MANUAL_GREEN:
		blinkingLed2Hz(HORIZONTAL_GREEN_GPIO_Port, HORIZONTAL_GREEN_Pin,
					   VERTICAL_GREEN_GPIO_Port, VERTICAL_GREEN_Pin);
		break;
	default:
		break;
	}

	if (timer7seg_flag == 1){
		//set timer for 1Hz frequency
		setTimer7seg(250);
		//updated index_led to stay in valid range, which is from 0 to 3
		if (index_led >= MAX_LED)
			index_led = 0;
		//update 7seg leds
		update7SEG(index_led++);
	}
}

