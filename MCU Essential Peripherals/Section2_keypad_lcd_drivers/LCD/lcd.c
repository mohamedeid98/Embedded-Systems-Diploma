/*
 * lcd.c
 *
 * Created: 6/25/2023 9:26:59 AM
 *  Author: Mohamed Eid
 */ 

#include "lcd.h"





void LCD_init()
{
	_delay_ms(20);
	
	LCD_CTRL_DIR |= ((1 << RS) | (1 << RW) | (1 << EN));
	
	
	#ifdef EIGHT_BIT_MODE
	LCD_DATA_DIR |= (0xFF << DATA_SHIFT);
	LCD_send_command(FUNCTION_SET_8_BIT_MODE);

	#endif

	#ifdef FOUR_BIT_MODE
	LCD_DATA_DIR |= (0xFF << DATA_SHIFT);
	LCD_send_command(0x02); //Sets to 4-bit operation. In this case, operation is handled as 8 bits by initialization, and only this instruction completes with one write.8
	
	LCD_send_command(FUNCTION_SET_4_BIT_MODE);
	
	#endif
	
	LCD_send_command(ENTRY_MODE_SET);
	LCD_send_command(0x01); //
	LCD_send_command(DISPLAY_ON_OFF_CONTROL);
	LCD_send_command(0x80);
}
/*
void LCD_lcd_kick()
{
	LCD_CTRL |= (1 << EN);
	_delay_ms(50);
	LCD_CTRL &= ~(1 << EN);
}
*/
/*
void LCD_busy_flag_check()
{
	LCD_DATA_DIR &= ~(0xFF << DATA_SHIFT);
	LCD_CTRL &= ~(1 << RS);
	LCD_CTRL |= (1 << RW);
	
	LCD_lcd_kick();
	LCD_DATA_DIR |= (0xFF << DATA_SHIFT);
	LCD_CTRL &= ~(1 << RW);
}
*/
void LCD_send_command(uint8_t command)
{
	LCD_CTRL &= ~ (1 << RS) | (1 << RW);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);
	
	#ifdef EIGHT_BIT_MODE

	
	LCD_DATA = command;
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);

	
	#endif

	#ifdef FOUR_BIT_MODE
	
	LCD_DATA = ((LCD_DATA & 0x0F) | (command & 0xF0));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);
	
	
	LCD_DATA = ((LCD_DATA & 0x0F) | (command << 4));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);
	
	
	#endif
}



void LCD_write_char(uint8_t character)
{
	
	#ifdef EIGHT_BIT_MODE
	LCD_CTRL |= (1 << RS);
	LCD_CTRL &= ~(1 << RW);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);
	LCD_DATA = character;
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);
	

	#endif

	#ifdef FOUR_BIT_MODE
	LCD_CTRL |= (1 << RS);
	LCD_CTRL &= ~(1 << RW);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);
	
	LCD_DATA = ((LCD_DATA & 0x0F) | (character & 0xF0));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);

	
	
	LCD_DATA = ((LCD_DATA & 0x0F) | (character << 4));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);

	#endif

}

void LCD_set_DDRAM_ADD(uint8_t position)
{
	LCD_send_command(position);
}



void LCD_write_string(char *string)
{
	int counter=0;
	while(*string > 0)
	{
		
		LCD_write_char(*string++);
		counter++;
		if(counter == 16)
		{
			LCD_send_command(SET_DDRAM_BEGIN_LINE2);
		}
		else if(counter == 32 || counter ==33)
		{
			LCD_send_command(CLEAR_DISPLAY);
			LCD_send_command(SET_DDRAM_BEGIN_LINE1);
			counter = 0;
		}
		
		
	}
}


void LCD_display_number(int number)
{
	char str[7];
	sprintf(str, "%d", number);
	LCD_write_string(str);
}


void LCD_clear_display()
{
	LCD_send_command(CLEAR_DISPLAY);
}