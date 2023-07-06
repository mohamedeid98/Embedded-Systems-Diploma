/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Eid
 * @brief          : Main program body
 ******************************************************************************/

#include <../STM32F103C6_Drivers/inc/STM32F103C6.h>
#include <../STM32F103C6_Drivers/inc/gpio.h>
#include "../STM32F103C6_Drivers/HAL/LCD_Driver/lcd.h"
#include "../STM32F103C6_Drivers/HAL/KEYPAD_Driver/keypad.h"
#include "../STM32F103C6_Drivers/HAL/7-SEG/segment.h"

unsigned char Segment[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
unsigned char LCD[] = {'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9'};


int main(void)
{

	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();


	LCD_init();
	Segment_Init();
	keypad_init();

	_delay_ms(1000);

	//LCD display startup message
	LCD_write_string("Hey");
	_delay_ms(1000);
	LCD_clear_display();

	//Displaying count from 0 to 9 untill keypad is ready
	for (unsigned char i=0 ; i<11 ; i++)
	{
		MCAL_GPIO_WritePort(SEGMENT_PORT ,  Segment[i] << 9);
		LCD_write_char(LCD[i]);
		_delay_ms(1000);
	}
	LCD_clear_display();
	LCD_write_string("Keypad is ready");
	_delay_ms(2000);
	LCD_clear_display();


	char key;
	/* Loop forever */
	while(1)
	{
		key = keypad_getkey();


		switch(key)
		{
		case 'A':
			break;
		case '?':
			LCD_clear_display();
			break;
		default:
			LCD_write_char(key);

		}


	}
}
