/*
 * UART_ATmega32.c
 *
 * Created: 8/6/2023 5:56:10 AM
 * Author : Mohamed Eid
 */ 

#include "MCAL/UART/uart.h"
#include "HAL/LCD/lcd.h"

int main(void) {

	char Txstr[] = "UART ATmega32";
	char RxStr[20];

	LCD_INIT();
	UART_Init();
	UART_SendString(Txstr);
    /* Replace with your application code */

    while (1) {
    
		UART_ReceiveString(RxStr);
		LCD_display_String(RxStr);
	}
}

