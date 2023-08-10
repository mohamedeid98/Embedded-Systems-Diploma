

#include <stdint.h>
#include "../MCAL/Inc/uart.h"


void USART_IRQ_Callback(void)
{
	uint16_t ch;
	MCAL_USART_Receive(USART1, &ch, disable);
	MCAL_USART_Send(USART1, &ch, enable);

}


int main(void)
{
	//Enable CLock
		RCC_GPIOA_CLK_EN();
		RCC_GPIOB_CLK_EN();
		RCC_AFIO_CLK_EN();

		USART_Config_t uartCFG ;
		uartCFG.BaudRate 		= USART_BuadRate_115200 ;
		uartCFG.HwFlowCtl 		= UART_HwFlowCtl_NONE ;
		uartCFG.IRQ_Enable		= USART_IRQ_Enable_RXNEIE ;
		uartCFG.P_IRQ_CallBack 	= USART_IRQ_Callback ;
		uartCFG.Parity 			= USART_Parity_disabled ;
		uartCFG.Payload_Length 	= USART_Payload_8_bits;
		uartCFG.Stop 			= USART_Stop__1 ;
		uartCFG.USART_Mode 		= USART_Mode_Tx_Rx ;

		MCAL_USART_Init(USART1, &uartCFG);

		while(1)
		{

		}
}
