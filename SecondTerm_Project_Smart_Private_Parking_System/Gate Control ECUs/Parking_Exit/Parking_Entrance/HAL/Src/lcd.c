/*
 * lcd.c
 *
 *  Author: Mohamed Eid
 */ 

#include "../Inc/lcd.h"



uint8_t firstCharAddr[] = {0x80, 0xC0, 0x94, 0xD4};
/****************************************************************************************
									LCD APIs Implementation
*****************************************************************************************/
/*void delay_us(uint32_t d)
{
	_delay_us(d);
}
*/
void HAL_LCD_send_command(uint8_t cmnd)
{

#ifdef FOUR_LINE_MODE
	LCD_DATA = (LCD_DATA & HIGHER_FOUR_PINS) | (cmnd & 0xF0);    //send high nibble to D4-D7
	LCD_CTRL &= ~(1 << RS);										 // Clear to select command register.
	LCD_CTRL &= ~(1 << RW);										 // Clear for write operation.
	
	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	LCD_CTRL |= (1 << EN);
	_delay_us(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_us(100);
	
	LCD_DATA = (LCD_DATA & HIGHER_FOUR_PINS) | (cmnd << 4);  // send low nibble to D4-D7
	
	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	LCD_CTRL |= (1 << EN);
	_delay_us(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_us(100);
	
#endif	

}

/***********************************************************************************/

void HAL_LCD_send_data(uint8_t data)
{
	
#ifdef FOUR_LINE_MODE
	LCD_DATA = (LCD_DATA & HIGHER_FOUR_PINS) | (data & 0xF0);
	LCD_CTRL |= (1 << RS);					// Set RS to select data register.
	LCD_CTRL &= ~(1 << RW);					// Clear for write operation.
	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	LCD_CTRL |= (1 << EN);
	_delay_us(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_us(100);
	
	LCD_DATA = (LCD_DATA & HIGHER_FOUR_PINS) | (data << 4);
	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	LCD_CTRL |= (1 << EN);
	_delay_us(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_us(100);


#endif
}

/**********************************************************************/
void HAL_LCD_Init()
{
	/* 1- Configure the control port and data port as output. */
	LCD_DATA_DIR = 0xFF;

	/* 2- Disable the LCD to prevent any interruption */
	LCD_CTRL &= ~(1 << EN);

#ifdef FOUR_LINE_MODE
	HAL_LCD_send_command(0x33);
	HAL_LCD_send_command(0x32);
	HAL_LCD_send_command(TWO_LINE_FOUR_BIT_MODE);
#endif	

	HAL_LCD_send_command(DISPLAY_ON_CURSOR_OFF);				// Display ON, Cursor ON.
	HAL_LCD_send_command(CLEAR_DISPLAY_SCREEN);					// Clear LCD.
	
	_delay_us(2000);										// Wait.
	HAL_LCD_send_command(SHIFT_CURSOR_RIGHT);					// Shift cursor right.

}

/****************************************************************************************************/
void HAL_LCD_gotoxy(uint8_t x, uint8_t y)
{
	HAL_LCD_send_command(firstCharAddr[y - 1] + x - 1);
	_delay_us(100);
}

/****************************************************************************************************/

void HAL_LCD_print(uint8_t* str)
{
	uint8_t count = 0;
	
	while(*str)
	{
		/*if(count == 16)
		{
			LCD_gotoxy(1, 2);
		}
		else if(count == 32)
		{
			LCD_send_command(CLEAR_DISPLAY_SCREEN);
			_delay_us(2000);
		}*/
		HAL_LCD_send_data(*str++);
		count++;
	}
}


void HAL_LCD_print_int_number(uint32_t num)
{
	uint8_t str[7];
	sprintf(str, "%ld", num);
	HAL_LCD_print((uint8_t*)str);
}





