/*
 * timer2.c
 *
 *      Author: Mohamed Eid
 */

#include "../Inc/timer2.h"

void MCAL_TIM2_Init()
{
	RCC_TIM2_CLK_EN();			/* Enable clock for timer2 */

	TIM2->PSC = 7;				/* With Fclk = 8MHz, Ftim2 = (8 / (1 + 7)) = 1MHz */


}

void MCAL_TIM2_Delay_uS(uint32_t delay)
{
	TIM2->ARR = delay;
	TIM2->CNT = 0X0000;
	TIM2->CR1 |= (1 << 0);     /* Enable timer2 */
	while(!(TIM2->SR & (1 << 0)));
	TIM2->CR1 &= ~(1 << 0);
	TIM2->SR = 0x0000;

//	TIM2->SR &= ~(1 << 0);
}

void MCAL_TIM2_Delay_mS(uint32_t delay)
{
	int i;
	for(i = 0 ; i < delay ; i++)
	{
		MCAL_TIM2_Delay_uS(1000);
	}
}
