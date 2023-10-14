/*
 * timer2.h
 *
 *  Created on: Sep 27, 2023
 *      Author: Mohamed
 */

#ifndef MCAL_INC_TIMER2_H_
#define MCAL_INC_TIMER2_H_

#include "../../Device_Header/STM32F103C6.h"


void MCAL_TIM2_Init();
void MCAL_TIM2_Delay_uS(uint32_t delay);
void MCAL_TIM2_Delay_mS(uint32_t delay);


#endif /* MCAL_INC_TIMER2_H_ */
