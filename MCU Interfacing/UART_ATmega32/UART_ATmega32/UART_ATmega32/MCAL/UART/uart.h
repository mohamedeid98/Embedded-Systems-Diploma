/*
 * uart.h
 *
 * Created: 8/6/2023 6:38:43 AM
 *  Author: Mohamed Eid
 */ 


#ifndef UART_H_
#define UART_H_

/*============================================================================================
									Includes
=============================================================================================*/


#include "../../Lib/ATmega32.h"

/*============================================================================================
									Generic Defines
=============================================================================================*/
#define TX_INTERRUPT_EN()					SET_BIT(UCSRB, TXCIE)
#define RX_INTERRUPT_EN()					SET_BIT(UCSRB, RXCIE)

#define TX_INTERRUPT_DISABLE()				CLEAR_BIT(UCSRB, TXCIE)
#define RX_INTERRUPT_DISABLE()				CLEAR_BIT(UCSRB, RXCIE)

/*============================================================================================
									APIs
=============================================================================================*/

void UART_Init(void);
void UART_Send(uint8  data);
uint8 UART_Receive(void);

void UART_SendNumber32(uint32 num);
uint32 UART_ReceiveNumber32(void);

void UART_SendString(char *TxStr);
void UART_ReceiveString(char *RxStr);

char* UART_Receive_String(void);

uint32 UART_ReceivePeriodic(char *RxBuff);


#endif /* UART_H_ */