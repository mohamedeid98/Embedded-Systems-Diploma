/*
 * keypad.h
 *
 * Created: 6/25/2023 9:30:37 AM
 *  Author: Mohamed Eid
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include<avr/io.h>
#include<util/delay.h>

#define R0	0
#define R1	1
#define R2	2
#define R3	3
#define C0	4
#define C1	5
#define C2	6
#define C3	7

#define KEYPAD_PORT	PORTC
#define	KEYPAD_DDR	DDRC
#define KEYPAD_PIN	PINC


void keypad_init();
char keypad_getkey();


#endif /* KEYPAD_H_ */
