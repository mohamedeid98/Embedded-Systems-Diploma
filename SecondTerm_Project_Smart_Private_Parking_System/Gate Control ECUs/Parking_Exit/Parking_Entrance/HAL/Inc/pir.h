/*
 * pir.h
 *
 *  Author: Mohamed Eid
 */ 


#ifndef PIR_H_
#define PIR_H_


#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>
#include<stdio.h>

#define PIR_PIN 3

void HAL_PIR_Init(volatile uint8_t* DDRx, uint8_t PINx);
uint8_t HAL_PIR_GetState(volatile uint8_t* PORTx, uint8_t PINx);



#endif /* PIR_H_ */