/*
 * 7seg.h
 *
 *      Author: Mohamed Eid
 */

#ifndef HAL_INC_7SEG_H_
#define HAL_INC_7SEG_H_


/********************************************************************************************
 										Includes
 ********************************************************************************************/
#include "../../MCAL/Inc/gpio.h"


/********************************************************************************************
 									Generic Macros
 ********************************************************************************************/

/* The interface with the micr-controller is through a BCD–to–seven–segment decoder
 * to decrease the number of pins used to interface with the seven segment.
 */
#define SEVEN_SEGMENT_PORT				GPIOA

#define SEVEN_SEGMENT_PIN1				GPIO_PIN12
#define SEVEN_SEGMENT_PIN2				GPIO_PIN13
#define SEVEN_SEGMENT_PIN3				GPIO_PIN14
#define SEVEN_SEGMENT_PIN4				GPIO_PIN15

#define PIN_SHIFT						12
/********************************************************************************************
* 											APIs
 ********************************************************************************************/

void HAL_7SEG_Init(void);
void HAL_7SEG_Update(uint8_t);
void HAL_7SEG_Reset(void);




#endif /* HAL_INC_7SEG_H_ */
