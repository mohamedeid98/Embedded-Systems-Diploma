/*
 * keypad.h
 *
 *      Author: Mohamed Eid
 */

#ifndef HAL_INC_KEYPAD_H_TXT_
#define HAL_INC_KEYPAD_H_TXT_

#include "../../MCAL/Inc/gpio.h"
#include "../../MCAL/Inc/timer2.h"

#define KEYPAD_INPUT			GPIOB
#define C1						GPIO_PIN5
#define C2						GPIO_PIN8
#define C3						GPIO_PIN9


#define KEYPAD_OUPUT			GPIOB

#define R1						GPIO_PIN0
#define R2						GPIO_PIN1
#define R3						GPIO_PIN3
#define R4						GPIO_PIN4

void HAL_Keypad_Init(void);
uint8_t HAL_Keypad_GetKey(void);


#endif /* HAL_INC_KEYPAD_H_TXT_ */
