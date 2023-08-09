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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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


void UART_SendString(char *TxStr){
	while(*TxStr){
		UART_Send(*TxStr++);
	}
}

void UART_ReceiveString(char *RxStr){
	
	char ch;
	
	while(1){
		
		ch = UART_Receive();
		if(ch == '#'){
			*RxStr = '\0';
			break;
		}
		*RxStr++ = ch;
	}
}

void UART_SendNumber32(uint32 num){
	
	char *Pnum = &num;
	UART_Send(*Pnum++);
	UART_Send(*Pnum++);
	UART_Send(*Pnum++);
	UART_Send(*Pnum);

}

uint32 UART_ReceiveNumber32(void){
	uint32_t number;

	char s1[9];
	char s2[9];
	char s3[9];
	char s4[9];

	sprintf(s1, "%d", (UART_Receive() - 48));
	sprintf(s2, "%d", (UART_Receive() - 48));
	sprintf(s3, "%d", (UART_Receive() - 48));
	sprintf(s4, "%d", (UART_Receive() - 48));
	strcat(s1, s2);
	strcat(s1, s3);
	strcat(s1, s4);
	number = atoi(s1);
	
	return number; 

}
