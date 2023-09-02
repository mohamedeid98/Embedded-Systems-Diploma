

#include <stdint.h>

#include "../MCAL/Inc/uart.h"
#include "../MCAL/Inc/spi.h"

#define MCU_ACT_AS_MASTER

void USART_IRQ_Callback(void)
{
	uint16_t ch;
	MCAL_USART_Receive(USART1, &ch, disable);
	MCAL_USART_Send(USART1, &ch, enable);

	MCAL_GPIO_WritePin (GPIOA, GPIO_PIN4, GPIO_PIN_RESET);
	MCAL_SPI_Send(SPI1, &ch, Polling_Enable);
	MCAL_SPI_Receive(SPI1, &ch, Polling_Enable);
	MCAL_GPIO_WritePin (GPIOA, GPIO_PIN4, GPIO_PIN_SET);

}



int main(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	USART_Config_t uartCFG ;

	uartCFG.BaudRate 		= USART_BuadRate_9600 ;
	uartCFG.HwFlowCtl 		= UART_HwFlowCtl_NONE ;
	uartCFG.IRQ_Enable		= USART_IRQ_Enable_RXNEIE ;
	uartCFG.P_IRQ_CallBack 	= USART_IRQ_Callback ;
	uartCFG.Parity 			= USART_Parity_disabled ;
	uartCFG.Payload_Length 	= USART_Payload_8_bits;
	uartCFG.Stop 			= USART_Stop__1 ;
	uartCFG.USART_Mode 		= USART_Mode_Tx_Rx ;

	MCAL_USART_Init(USART1, &uartCFG);

	SPI_Config_t spiConfig;

	spiConfig.BaudRate_PreScaler = SPI_BR_fPCLK_8;
	spiConfig.Communication_Mode = SPI_COMM_MODE_FULL_DUPLEX;
	spiConfig.CLK_Polarity = SPI_CPOL_IDLE_LOW;
	spiConfig.CLK_Phase = SPI_CPHA_2ND_EDGE;
	spiConfig.Frame_Size = SPI_FRAME_SIZE_8bits;
	spiConfig.Frame_Format = SPI_DFF_MSB;

#ifdef MCU_ACT_AS_MASTER
	spiConfig.NSS_MODE = SPI_NSS_MODE_SW_SET;
	spiConfig.Mode = SPI_MODE_MASTER;
	spiConfig.INT_Enable = SPI_INT_DISABLE;
	spiConfig.P_CallBack = NULL;
#endif


	MCAL_SPI_Init(SPI1, &spiConfig);

	GPIO_PinConfig_t pinConfig;

	pinConfig.GPIO_PinNumber = GPIO_PIN4;
	pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;

	MCAL_GPIO_Init(GPIOA, &pinConfig);

	while(1)
	{

    }
}
