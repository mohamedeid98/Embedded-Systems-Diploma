/*
 * led.h
 *
 *  Author: Mohamed Eid
 */ 


#ifndef LED_H_
#define LED_H_

#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>
#include<stdio.h>

#define SET_BIT(REG, BIT_NUM)        (REG |= (1<<BIT_NUM))                             // set bit in reg.
#define CLEAR_BIT(REG, BIT_NUM)      (REG &= (~(1<<BIT_NUM)))                          // clear bit in reg.
#define TOGGLE_BIT(REG, BIT_NUM)     (REG ^= (1<<BIT_NUM))                             // toggle bit in reg.



void HAL_LED_ON(volatile uint8_t* PORTx, uint8_t PINx);
void HAL_LED_OFF(volatile uint8_t* PORTx, uint8_t PINx);

#endif /* LED_H_ */