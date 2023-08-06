/*
 * segment.h
 *
 *  Created on: Jul 5, 2023
 *      Author: Mohamed
 */

#ifndef HAL_7_SEG_SEGMENT_H_
#define HAL_7_SEG_SEGMENT_H_

#include "../../inc/STM32F103C6.h"
#include "../../inc/gpio.h"

#define SEGMENT_PORT           GPIOB
#define SEGMENT_PIN1           GPIO_PIN9
#define SEGMENT_PIN2           GPIO_PIN10
#define SEGMENT_PIN3           GPIO_PIN11
#define SEGMENT_PIN4           GPIO_PIN12
#define SEGMENT_PIN5           GPIO_PIN13
#define SEGMENT_PIN6           GPIO_PIN14
#define SEGMENT_PIN7           GPIO_PIN15



#define ZERO              	   0x01
#define ONE                	   0x79
#define TWO                    0x24
#define THREE                  0x30
#define FOUR                   0x4C
#define FIVE                   0x12
#define SIX                    0x02
#define SEVEN                  0x19
#define EIGHT                  0x00
#define NINE                   0x10

void Segment_Init();


#endif /* HAL_7_SEG_SEGMENT_H_ */
