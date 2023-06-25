/*
 * LCD_KEYPAD.c
 *
 * Created: 6/25/2023 9:26:07 AM
 * Author : Mohamed
 */ 
#include "LCD/lcd.h"
#include "KEYPAD/keypad.h"




int main(void)
{
	char key;
	LCD_init();
	keypad_init();
	
    while (1) 
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
		//_delay_ms(100);
    
	}
}

