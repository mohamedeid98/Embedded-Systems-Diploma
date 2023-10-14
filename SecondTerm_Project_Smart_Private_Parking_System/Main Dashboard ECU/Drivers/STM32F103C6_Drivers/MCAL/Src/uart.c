/*
 * uart.c
 *
 *  Created on: Aug 9, 2023
 *      Author: Mohamed Eid
 */

/*
 * =======================================================================================
 * 							Includes
 * =======================================================================================
 */

#include "../Inc/uart.h"



/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */


USART_Config_t G_USART_CONFIG[3];


/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */

#define USART1_IDX			0
#define USART2_IDX			1
#define USART3_IDX			2

/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

/**================================================================
 * @Fn				- UART_GPIO_Set_Pins
 * @brief 			- Initialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- None
 * Note				- Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_UART_Init()
 */
void UART_GPIO_Set_Pins (USART_TypeDef *USARTx)
{
	GPIO_PinConfig_t pinCfg;


	if (USARTx == USART1)
	{
		//PA9 TX
		pinCfg.GPIO_PinNumber 	= GPIO_PIN9;
		pinCfg.GPIO_PinMode 	= GPIO_MODE_OUTPUT_AF_PP;
		pinCfg.GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		//PA10 RX
		pinCfg.GPIO_PinNumber 	= GPIO_PIN10;
		pinCfg.GPIO_PinMode 	= GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		/*if (G_USART_CONFIG[USART1_IDX].HwFlowCtl == UART_HwFlowCtl_CTS || G_USART_CONFIG[USART1_IDX].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA11 CTS
			pinCfg.GPIO_PinNumber 	= GPIO_PIN11;
			pinCfg.GPIO_PinMode 	= GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinCfg);

		}
		else if (G_USART_CONFIG[USART1_IDX].HwFlowCtl == UART_HwFlowCtl_RTS || G_USART_CONFIG[USART1_IDX].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA12 RTS
			pinCfg.GPIO_PinNumber 	= GPIO_PIN12;
			pinCfg.GPIO_PinMode 	= GPIO_MODE_OUTPUT_AF_PP;
			pinCfg.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinCfg);

		}*/
	}


	else if (USARTx == USART2)
	{
		//PA2 TX
		pinCfg.GPIO_PinNumber 	= GPIO_PIN2;
		pinCfg.GPIO_PinMode 	= GPIO_MODE_OUTPUT_AF_PP;
		pinCfg.GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		//PA3 RX
		pinCfg.GPIO_PinNumber 	= GPIO_PIN3;
		pinCfg.GPIO_PinMode 	= GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &pinCfg);

		/*if (G_USART_CONFIG[USART2_IDX].HwFlowCtl == UART_HwFlowCtl_CTS || G_USART_CONFIG[USART2_IDX].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA0 CTS
			pinCfg.GPIO_PinNumber 	= GPIO_PIN0;
			pinCfg.GPIO_PinMode 	= GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinCfg);

		}
		else if (G_USART_CONFIG[USART2_IDX].HwFlowCtl == UART_HwFlowCtl_RTS || G_USART_CONFIG[USART2_IDX].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA1 RTS
			pinCfg.GPIO_PinNumber 	= GPIO_PIN1;
			pinCfg.GPIO_PinMode 	= GPIO_MODE_OUTPUT_AF_PP;
			pinCfg.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinCfg);

		}*/
	}


	else if (USARTx == USART3)
	{
		//PB10 TX
		pinCfg.GPIO_PinNumber 	= GPIO_PIN10;
		pinCfg.GPIO_PinMode 	= GPIO_MODE_OUTPUT_AF_PP;
		pinCfg.GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinCfg);

		//PB11 RX
		pinCfg.GPIO_PinNumber 	= GPIO_PIN11;
		pinCfg.GPIO_PinMode 	= GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &pinCfg);

		if (G_USART_CONFIG[USART3_IDX].HwFlowCtl == UART_HwFlowCtl_CTS || G_USART_CONFIG[USART3_IDX].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PB13 CTS
			pinCfg.GPIO_PinNumber 	= GPIO_PIN13;
			pinCfg.GPIO_PinMode 	= GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinCfg);

		}
		else if (G_USART_CONFIG[USART3_IDX].HwFlowCtl == UART_HwFlowCtl_RTS || G_USART_CONFIG[USART3_IDX].HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PB14 RTS
			pinCfg.GPIO_PinNumber 	= GPIO_PIN14;
			pinCfg.GPIO_PinMode 	= GPIO_MODE_OUTPUT_AF_PP;
			pinCfg.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinCfg);

		}
	}
}

/*
 * =======================================================================================
 * 							APIs Implementation
 * =======================================================================================
 */


/**================================================================
 * @Fn				- MCAL_USART_Init
 * @brief 			- Initializes the USARTx according to the specified parameters in the USART_Config
 * @param [in] 		- USARTx: where x can be (1 -> 3 depending on device used) to select the USART peripheral
 * @param [in] 		- USART_Config: pointer to a USART_Config_t structure that contains the configuration of the peripheral
 * @retval 			- None
 */
void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config_t* USART_Config)
{
	UART_GPIO_Set_Pins(USARTx);


	uint32_t pclk ,BRR_value  ;

	// Store the configuration structure to a global variable to be seen by all functions using it.
	if(USARTx == USART1)
	{
		G_USART_CONFIG[USART1_IDX] = *USART_Config;
	}
	else if (USARTx == USART2)
	{
		G_USART_CONFIG[USART2_IDX] = *USART_Config;
	}
	else if (USARTx == USART3)
	{
		G_USART_CONFIG[USART3_IDX] = *USART_Config;
	}

	// Enable clock for the given USART peripheral
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
	}
	else if (USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
	}
	else if (USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
	}


	// Enable the USART by writing the UE bit in USART_CR1 register to 1.
	USARTx->CR1 |= (1 << 13);

	// Program the M bit in USART_CR1 to define the word length.
	USARTx->CR1 |= USART_Config->Payload_Length;

	// Program the number of stop bits in USART_CR2.
	USARTx->CR2 |= USART_Config->Stop;

	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2, 3
	//PCLK2 for USART1

	// Baud rate configuration
	if (USARTx == USART1)
	{
		pclk = MCAL_RCC_GetPCLK2Freq() ;
	}
	else
	{
		pclk = MCAL_RCC_GetPCLK1Freq() ;
	}

	BRR_value = UART_BRR_Register(pclk,USART_Config->BaudRate) ;
	USARTx->BRR |= BRR_value ;


	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	//	USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= USART_Config->USART_Mode ;

	// Program the parity bit mode
	USARTx->CR1 |= USART_Config->Parity;

	// USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR3 |= USART_Config->HwFlowCtl;

	//ENABLE / DISABLE Interrupt
	if (USART_Config->IRQ_Enable != USART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= USART_Config->IRQ_Enable;

		// Clear the target USART mask on NVIC
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_ENABLE();
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_ENABLE();
		}
		else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_ENABLE();
		}
	}


}


/**================================================================
 * @Fn				- MCAL_USART_DeInit
 * @brief 			- Reset the USARTx according to the specified parameters in the USARTx
 * @param [in] 		- USARTx: where x can be (1 -> 3 depending on device used) to select the USART peripheral
 * @retval 			- None
 * Note				- Reset the module by RCC.
 */
void MCAL_USART_DeInit(USART_TypeDef *USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_RESET();
		NVIC_IRQ37_USART1_DISABLE();
	}

	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_RESET();
		NVIC_IRQ38_USART2_DISABLE();
	}

	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_RESET();
		NVIC_IRQ39_USART3_DISABLE();
	}


}


/*********************************************************************
 * @fn      		  - MCAL_USART_Send
 *
 * @brief             - Send Buffer on UART
 *
 * @param [in] 		  - USARTx: where x can be (1..3 depending on device used)
 * @param[in]         - pTxBuffer Buffer
 * @param[in]         - PollingEn   Enable pooling or disable it
 *
 * @return            - None
 * @Note              - Should initialize UART First
 * 						When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
						because it is replaced by the parity.
						When receiving with the parity enabled, the value read in the MSB bit is the received parity
						bit

 */

void MCAL_USART_Send(USART_TypeDef *USARTx, uint8_t pTxBuffer, Polling_mechism PollingEn)
{
	if (PollingEn == USART_polling_enable)
	{
		while(!(USARTx->SR & (1 << 7)));
	}

	USARTx->DR = pTxBuffer;

	/*if (USARTx == USART1)
	{
		if(G_USART_CONFIG[USART1_IDX].Payload_Length == USART_Payload_9_bits)
		{
			USARTx->DR = ((*pTxBuffer) & (uint16_t)0x01FF);
		}
		else if (G_USART_CONFIG[USART1_IDX].Payload_Length == USART_Payload_8_bits)
		{
			USARTx->DR = ((*pTxBuffer) & (uint8_t)0xFF);
		}
	}

	else if (USARTx == USART2)
	{
		if(G_USART_CONFIG[USART2_IDX].Payload_Length == USART_Payload_9_bits)
		{
			USARTx->DR = ((*pTxBuffer) & (uint16_t)0x01FF);
		}
		else if (G_USART_CONFIG[USART2_IDX].Payload_Length == USART_Payload_8_bits)
		{
			USARTx->DR = ((*pTxBuffer) & (uint8_t)0xFF);
		}
	}

	else if (USARTx == USART3)
	{
		if(G_USART_CONFIG[USART3_IDX].Payload_Length == USART_Payload_9_bits)
		{
			USARTx->DR = ((*pTxBuffer) & (uint16_t)0x01FF);
		}
		else if (G_USART_CONFIG[USART3_IDX].Payload_Length == USART_Payload_8_bits)
		{
			USARTx->DR = ((*pTxBuffer) & (uint8_t)0xFF);
		}
	}*/
}


/*********************************************************************
 * @fn      		  - MCAL_USART_Receive
 *
 * @brief             - Send Buffer on UART
 *
 * @param [in] 		  - USARTx: where x can be (1..3 depending on device used)
 * @param[in]         - pTxBuffer Buffer
 * @param[in]         - PollingEn   Enable pooling or disable it
 *
 * @return            - None
 * @Note              - Should initialize UART First
 * 						When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
						because it is replaced by the parity.
						When receiving with the parity enabled, the value read in the MSB bit is the received parity
						bit

 */

void MCAL_USART_Receive(USART_TypeDef *USARTx, uint16_t *pRxBuffer, Polling_mechism PollingEn)
{
	if (PollingEn == USART_polling_enable)
	{
		while(!(USARTx->SR & (1 << 5)));
	}

	*pRxBuffer = USARTx->DR ;

	/*if (USARTx == USART1)
	{
		// if the parity bit is enabled
		if(G_USART_CONFIG[USART1_IDX].Parity != USART_Parity_disabled)
		{
			if (G_USART_CONFIG[USART1_IDX].Payload_Length == USART_Payload_9_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );
			}
			else if (G_USART_CONFIG[USART1_IDX].Payload_Length == USART_Payload_8_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0x7F );
			}
		}
		// If there is no parity
		else if (G_USART_CONFIG[USART1_IDX].Parity == USART_Parity_disabled)
		{
			if (G_USART_CONFIG[USART1_IDX].Payload_Length == USART_Payload_9_bits)
			{
				*((uint16_t*) pRxBuffer) = USARTx->DR ;
			}
			else if (G_USART_CONFIG[USART1_IDX].Payload_Length == USART_Payload_8_bits)
			{
				// *((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF ) ;
				*pRxBuffer = USARTx->DR & 0xFF;
			}
		}
	}

	else if (USARTx == USART2)
	{
		// if the parity bit is enabled
		if(G_USART_CONFIG[USART2_IDX].Parity != USART_Parity_disabled)
		{
			if (G_USART_CONFIG[USART2_IDX].Payload_Length == USART_Payload_9_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );
			}
			else if (G_USART_CONFIG[USART2_IDX].Payload_Length == USART_Payload_8_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0x7F );
			}
		}
		// If there is no parity
		else if (G_USART_CONFIG[USART2_IDX].Parity == USART_Parity_disabled)
		{
			if (G_USART_CONFIG[USART2_IDX].Payload_Length == USART_Payload_9_bits)
			{
				*((uint16_t*) pRxBuffer) = USARTx->DR ;
			}
			else if (G_USART_CONFIG[USART2_IDX].Payload_Length == USART_Payload_8_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF ) ;
			}
		}
	}


	else if (USARTx == USART3)
	{
		// if the parity bit is enabled
		if(G_USART_CONFIG[USART3_IDX].Parity != USART_Parity_disabled)
		{
			if (G_USART_CONFIG[USART3_IDX].Payload_Length == USART_Payload_9_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );
			}
			else if (G_USART_CONFIG[USART3_IDX].Payload_Length == USART_Payload_8_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0x7F );
			}
		}
		// If there is no parity
		else if (G_USART_CONFIG[USART3_IDX].Parity == USART_Parity_disabled)
		{
			if (G_USART_CONFIG[USART3_IDX].Payload_Length == USART_Payload_9_bits)
			{
				*((uint16_t*) pRxBuffer) = USARTx->DR ;
			}
			else if (G_USART_CONFIG[USART3_IDX].Payload_Length == USART_Payload_8_bits)
			{
				*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF ) ;
			}
		}
	}*/


}



/*
 * =======================================================================================
 * 										ISR
 * =======================================================================================
 */

void USART1_IRQHandler (void)
{

	G_USART_CONFIG[USART1_IDX].P_IRQ_CallBack () ;

}

void USART2_IRQHandler (void)
{
	G_USART_CONFIG[USART2_IDX].P_IRQ_CallBack () ;

}
void USART3_IRQHandler (void)
{
	G_USART_CONFIG[USART3_IDX].P_IRQ_CallBack () ;

}





