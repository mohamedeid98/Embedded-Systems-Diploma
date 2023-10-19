/*
 * led.c
 *
 *  Author: Mohamed Eid
 */ 

#include "../Inc/led.h"


void HAL_LED_ON(volatile uint8_t* PORTx, uint8_t PINx)
{
	*(PORTx - 1) |= (1 << PINx);	// Set DDRx
	*PORTx |= (1 << PINx);			// Set the pin high
}

void HAL_LED_OFF(volatile uint8_t* PORTx, uint8_t PINx)
{
	*(PORTx - 1) |= (1 << PINx);	// Set DDRx
	*PORTx &= ~(1 << PINx);			// Set the pin low
}