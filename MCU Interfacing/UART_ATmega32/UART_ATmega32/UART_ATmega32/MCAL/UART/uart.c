/*
 * uart.c
 *
 * Created: 8/6/2023 6:37:41 AM
 *  Author: Mohamed Eid
 */ 


/*============================================================================================
									Includes
=============================================================================================*/

#include "uart.h"



/*============================================================================================
									Functions Implementation
=============================================================================================*/


void UART_Init(void){
	
	CLEAR_BIT(UCSRA, U2X);  // Normal MODE
	
	// Set BaudRate to 9600 using 8 MHz crystal
	UBRRH = 0 ;
	UBRRL = 51;
	
	// Character Size --> 8 bit mode
	SET_BIT(UCSRC, UCSZ0);
	SET_BIT(UCSRC, UCSZ1);
	CLEAR_BIT(UCSRB, UCSZ2);
	
	// Asynchronous Mode
	CLEAR_BIT(UCSRC, UMSEL);
	
	// Parity Mode --> Disabled
	CLEAR_BIT(UCSRC, UPM0);
	CLEAR_BIT(UCSRC, UPM1);
	
	// Stop bit select --> 1 bit stop
	CLEAR_BIT(UCSRC, USBS);
	
	// Enable Rx and Tx
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);
}


void UART_Send(uint8 data){
	
	while(!(READ_BIT(UCSRA, UDRE)));
	UDR = data;
}

uint8 UART_Receive(void){
	
	while(!(READ_BIT(UCSRA, RXC)));
	
	return UDR;
}
