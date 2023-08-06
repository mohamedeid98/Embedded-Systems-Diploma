/*
 * UART_ATmega32.c
 *
 * Created: 8/6/2023 5:56:10 AM
 * Author : Mohamed Eid
 */ 

#include "MCAL/UART/uart.h"
#include "HAL/LCD/lcd.h"

int main(void)
{
	LCD_INIT();
	UART_Init();
	LCD_Display_Character('M');
	UART_Send('M');
    /* Replace with your application code */
    while (1) 
    {
		char x = UART_Receive();
		LCD_Display_Character(x);
    }
}

