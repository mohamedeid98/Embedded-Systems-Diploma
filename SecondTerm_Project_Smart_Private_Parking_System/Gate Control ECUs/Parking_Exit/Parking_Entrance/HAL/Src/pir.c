/*
 * pir.c
 *
 *  Author: Mohamed Eid
 */ 

#include "../Inc/pir.h"

void HAL_PIR_Init(volatile uint8_t* DDRx, uint8_t PINx)
{
	*DDRx &= ~(1 << PINx);	// Clear DDRx
}


uint8_t HAL_PIR_GetState(volatile uint8_t* PORTx, uint8_t PINx)
{
	uint8_t state = ((*PORTx & (1 << PINx)) >> PINx);
	return state;
}


