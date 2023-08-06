/*
 * lcd.h
 *
 * Created: 6/25/2023 9:27:08 AM
 *  Author: Mohamed Eid
 */ 


#ifndef LCD_H_
#define LCD_H_


#include "../../MCAL/Inc/STM32F103C6.h"
#include "../../MCAL/Inc/gpio.h"

#include<stdint.h>
#include<stdio.h>

#define LCD_DATA				GPIOA
#define LCD_CTRL				GPIOA
#define EN						GPIO_PIN10
#define RW						GPIO_PIN9
#define	RS						GPIO_PIN8

//#define FOUR_BIT_MODE
#define EIGHT_BIT_MODE

#ifdef FOUR_BIT_MODE
#define DATA_SHIFT				4
#endif

#ifdef EIGHT_BIT_MODE
#define DATA_SHIFT				0
#endif

#define CLEAR_DISPLAY			0x01
#define	RETURN_HOME				0x02
#define ENTRY_MODE_SET			0x06
#define	DISPLAY_ON_OFF_CONTROL	0x0F
//#define CURSOR_OR_DISPLAY_SHIFT
#define FUNCTION_SET_8_BIT_MODE	0x38
#define FUNCTION_SET_4_BIT_MODE	0x28
//#define SET_CGRAM_ADD			0b0001(6-bit address)
//#define SET_DDRAM_ADD			0b001(7-bit address)
//#define READ_BUSY_FLAG			RS->0, RW->1, Read DB7
//#define WRITE_DATA				RS->1, RW->0, (8-bit data)
#define SET_DDRAM_BEGIN_LINE1	0x80
#define SET_DDRAM_BEGIN_LINE2	0xC0
#define CURSOR_OFF				0x0C

void LCD_init();
void LCD_send_command(uint8_t command);
void LCD_write_char(uint8_t character);
void LCD_write_string(char *string);
void LCD_busy_flag_check(void);
void LCD_lcd_kick(void);
void LCD_clear_screen(void);
void LCD_set_DDRAM_ADD(uint8_t position);
void LCD_display_number(int number);
void LCD_display_real_number(double number);

void LCD_clear_display();


void LCD_display_real_number(double number);
void _delay_ms(uint32_t m_sec);

#endif /* LCD_H_ */

