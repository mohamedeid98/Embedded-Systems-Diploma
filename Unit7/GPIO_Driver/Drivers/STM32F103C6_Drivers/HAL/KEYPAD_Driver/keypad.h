/*
 * keypad.h
 *
 * Created: 6/25/2023 9:30:37 AM
 *  Author: Mohamed Eid
*/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../inc/STM32F103C6.h"
#include "../../inc/gpio.h"

#include<stdint.h>
#include<stdio.h>

#define R0					GPIO_PIN0
#define R1					GPIO_PIN1
#define R2					GPIO_PIN3
#define R3					GPIO_PIN4
#define C0					GPIO_PIN5
#define C1					GPIO_PIN6
#define C2					GPIO_PIN7
#define C3					GPIO_PIN8

#define KEYPAD_PORT			GPIOB

#define PORT_SHIFT  		0

void keypad_init();
char keypad_getkey();


#endif /* KEYPAD_H_ */
