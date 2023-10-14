/*
 * lcd.h
 *
 *  Author: Mohamed Eid
 */ 


#ifndef LCD_H_
#define LCD_H_


#include<stdint.h>
#include<stdio.h>
#include<string.h>

#include "../../MCAL/Inc/gpio.h"


#define LCD_DATA				GPIOB

#define D4						GPIO_PIN12 /*************** Note *****************/
#define D5						GPIO_PIN13 /** Data pins					   	   **/
#define D6						GPIO_PIN14 /**			must be                **/
#define D7						GPIO_PIN15 /**					consecutive	   **/


#define LCD_CTRL				GPIOA

#define EN						GPIO_PIN8
#define RW						GPIO_PIN1
#define	RS						GPIO_PIN0

#define SHIFT					12

//#define EIGHT_LINE_MODE
#define FOUR_LINE_MODE

/****************************************************************************************
								 LCD Command Codes 
*****************************************************************************************/
#define CLEAR_DISPLAY_SCREEN						0x01
#define RETURN_HOME									0x02
#define SHIFT_CURSOR_LEFT							0x04
#define SHIFT_CURSOR_RIGHT							0x06
#define SHIFT_DISPLAY_RIGHT							0x05
#define SHIFT_DISPLAY_LEFT							0x07
#define DISPLAY_OFF_CURSOR_OFF						0x08
#define DISPLAY_OFF_CURSOR_ON						0x0A
#define DISPLAY_ON_CURSOR_OFF						0x0C
#define DISPLAY_ON_CURSOR_ON						0x0E 
#define DISPLAY_ON_CURSOR_BLINK						0x0F 
#define SHIFT_CURSOR_POS_LEFT						0x10
#define SHIFT_CURSOR_POS_RIGHT						0x14
#define SHIFT_ENTIRE_DISPLAY_LEFT					0x18
#define SHIFT_ENTIRE_DISPLAY_RIGHT					0x1C
#define FORCE_CURSOR_1ST_LINE						0x80
#define FORCE_CURSOR_2ND_LINE						0xC0
#define TWO_LINE_EIGHT_BIT_MODE						0x38		
#define TWO_LINE_FOUR_BIT_MODE						0x28

/****************************************************************************************
									LCD APIs 
*****************************************************************************************/


void LCD_Init();
void LCD_send_command(uint8_t cmnd);
void LCD_send_data(uint8_t data);
void LCD_gotoxy(uint8_t x, uint8_t y);
void LCD_print(uint8_t* str);
void LCD_print_int_number(uint32_t num);

void _delay_us(uint32_t t);

#endif /* LCD_H_ */

