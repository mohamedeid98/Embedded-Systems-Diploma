/*
 * timer.c
 *
 * Created: 8/22/2023 2:43:15 AM
 *  Author: Mohamed
 */ 
#include "timer.h"

PTR_CallBack_FUN OverFlow;
PTR_CallBack_FUN CompMatch;

void TIMER0_Init(TIMER0_CONFIG_t *timer_config)
{
	OverFlow = timer_config->TIMER0_CALLBACK_Overflow_INTERRUPT;
	CompMatch = timer_config->TIMER0_CALLBACK_CompareMatch_INTERRUPT;
	TCCR0 |= timer_config->mode | timer_config->clk_source; // Set the mode and clock source
		
	TIMSK |= timer_config->OCInterrupt | timer_config->TOInterrupt; // Set interrupts configuration
}

void TIMER0_Stop(void)
{
	TCCR0 |= NO_CLK_SRC;
}

void TIMER0_SetCompVal(uint8_t CompVal)
{
	OCR0 = CompVal;
}

uint8_t TIMER0_GetCompVal(void)
{
	return OCR0;
}

void TIMER0_SetCountVal(uint8_t countVal)
{
	TCNT0 = countVal;
}

uint8_t TIMER0_GetCountVal(void)
{
	return TCNT0;
}

ISR(TIMER0_COMP_vect)
{
	CompMatch();
}

ISR(TIMER0_OVF_vect)
{
	//u8_TOVNumber++;
	OverFlow();
}