/*
 * spi.c
 *
 *  Created on: Aug 30, 2023
 *      Author: Mohamed Eid
 */


/************************************************************************
								INCLUDES
 *************************************************************************/
#include "../Inc/spi.h"


/************************************************************************
							  Generic Macros
 *************************************************************************/
#define SPI1_IDX			0
#define SPI2_IDX			1

#define SPE					6 // SPI ENABLE
#define TXE_FLAG			1 // Transmit buffer empty
#define RXNE_FLAG			0 // Receive buffer not empty
#define OVR_FLAG			6 // overrun error interrupt
#define MODF_FLAG			5 // mode fault error interrupt


/************************************************************************
							Generic Variables
 *************************************************************************/
SPI_Config_t* G_SPI_CONFIG[2] = {NULL, NULL};



/************************************************************************
							Private Functions
 *************************************************************************/

/**================================================================
 * @Fn				- SPI_GPIO_Set_Pins
 * @brief 			- Initializes the SPIx GPIO pins according to the specified parameters in the SPI_Config
 * @param [in] 		- SPIx: where x can be (1 OR 2 depending on device used) to select the SPI peripheral
 * @retval 			- None
 * Note				- Support the full duplex mode only
 */

static void SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t pinConfig;

	if(SPIx == SPI1)
	{
		/* SPI1 Pins
		 * NSS 		----> PA4
		 * SCK 		----> PA5
		 * MISO 	----> PA6
		 * MOSI 	----> PA7
		 */

		/* SPI1_SCK Configuration */
		if (G_SPI_CONFIG[SPI1_IDX]->Mode == SPI_MODE_MASTER)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN5;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI1_IDX]->Mode == SPI_MODE_SLAVE)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN5;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

		/* SPI1_MOSI Configuration*/
		if (G_SPI_CONFIG[SPI1_IDX]->Mode == SPI_MODE_MASTER)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN7;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI1_IDX]->Mode == SPI_MODE_SLAVE)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN7;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

		/* SPI1_MISO */
		if (G_SPI_CONFIG[SPI1_IDX]->Mode == SPI_MODE_MASTER)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN6;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI1_IDX]->Mode == SPI_MODE_SLAVE)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN6;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

		/* SPI1_NSS */
		if (G_SPI_CONFIG[SPI1_IDX]->NSS_MODE == SPI_NSS_MODE_SLAVE_HW || G_SPI_CONFIG[SPI1_IDX]->NSS_MODE == SPI_NSS_MODE_MASTER_HW_INPUT)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN4;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI1_IDX]->NSS_MODE == SPI_NSS_MODE_MASTER_HW_OUTPUT)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN6;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

	}
	else if (SPIx == SPI2)
	{
		/* SPI2 Pins
		 * NSS 		----> PB12
		 * SCK 		----> PB13
		 * MISO 	----> PB14
		 * MOSI 	----> PB15
		 */

		/* SPI2_SCK Configuration */
		if (G_SPI_CONFIG[SPI2_IDX]->Mode == SPI_MODE_MASTER)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN13;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI2_IDX]->Mode == SPI_MODE_SLAVE)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN13;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}

		/* SPI2_MOSI Configuration*/
		if (G_SPI_CONFIG[SPI2_IDX]->Mode == SPI_MODE_MASTER)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN15;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI2_IDX]->Mode == SPI_MODE_SLAVE)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN15;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}

		/* SPI2_MISO */
		if (G_SPI_CONFIG[SPI2_IDX]->Mode == SPI_MODE_MASTER)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN14;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI2_IDX]->Mode == SPI_MODE_SLAVE)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN14;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}

		/* SPI2_NSS */
		if (G_SPI_CONFIG[SPI2_IDX]->NSS_MODE == SPI_NSS_MODE_SLAVE_HW || G_SPI_CONFIG[SPI2_IDX]->NSS_MODE == SPI_NSS_MODE_MASTER_HW_INPUT)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN12;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}
		else if (G_SPI_CONFIG[SPI2_IDX]->NSS_MODE == SPI_NSS_MODE_MASTER_HW_OUTPUT)
		{
			pinConfig.GPIO_PinNumber = GPIO_PIN12;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}


	}
}

/************************************************************************
						   APIs Implementation
 *************************************************************************/

/**================================================================
 * @Fn				- MCAL_SPI_Init
 * @brief 			- Initializes the SPIx according to the specified parameters in the SPI_Config
 * @param [in] 		- SPIx: where x can be (1 OR 2 depending on device used) to select the SPI peripheral
 * @param [in] 		- SPI_Config: pointer to a SPI_Config_t structure that contains the configuration of the SPI
 * @retval 			- None
 * Note				- Support the full duplex mode only
 */

void MCAL_SPI_Init(SPI_TypeDef* SPIx, SPI_Config_t* SPI_Config)
{
	uint32_t CR1_Config = 0;
	uint32_t CR2_Config = 0;

	if(SPIx == SPI1)
	{
		G_SPI_CONFIG[SPI1_IDX] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		G_SPI_CONFIG[SPI2_IDX] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	CR1_Config |= SPI_Config->BaudRate_PreScaler;
	CR1_Config |= SPI_Config->CLK_Polarity;
	CR1_Config |= SPI_Config->CLK_Phase;
	CR1_Config |= SPI_Config->Frame_Size;
	CR1_Config |= SPI_Config->Frame_Format;

	if (SPI_Config->NSS_MODE == SPI_NSS_MODE_MASTER_HW_OUTPUT)
	{
		CR2_Config |= SPI_Config->NSS_MODE;
	}
	else
	{
		CR1_Config |= SPI_Config->NSS_MODE;
	}

	CR1_Config |= SPI_Config->Communication_Mode;
	CR1_Config |= SPI_Config->Mode;

	if (SPI_Config->INT_Enable != SPI_INT_DISABLE)
	{
		CR2_Config |= SPI_Config->INT_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_ENABLE();
		}
		else if (SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_ENABLE();
		}
	}

	/* The SPE bit must be set */
	CR1_Config |= (1 << SPE);

	SPIx->CR1 = CR1_Config;
	SPIx->CR2 = CR2_Config;


	SPI_GPIO_Set_Pins(SPIx);
}

/**================================================================
 * @Fn				- MCAL_SPI_DeInit
 * @brief 			- Reset the SPIx registers
 * @param [in] 		- SPIx: where x can be (1 OR 2 depending on device used) to select the SPI peripheral
 * @retval 			- None
 * Note				- None
 */
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx)
{
	SPIx->CR1 &= ~(1 << SPE);

	if (SPIx == SPI1)
	{
		RCC_SPI1_CLK_RESET();
		NVIC_IRQ35_SPI1_DISABLE();
	}
	else if (SPIx == SPI2)
	{
		RCC_SPI2_CLK_RESET();
		NVIC_IRQ36_SPI2_DISABLE();
	}
}

/**================================================================
 * @Fn				- MCAL_SPI_Send
 * @brief 			- Send the data of the pTxBuffer of SPI.
 * @param [in] 		- SPIx: where x can be (1 OR 2 depending on device used) to select the SPI peripheral
 * @param [in]		- pTxBuffer: A pointer to the transmit buffer data.
 * @param [in]		- Polling: Parameter to check whether polling is enabled or not.
 * @retval 			- None
 * Note				- None
 */

void MCAL_SPI_Send(SPI_TypeDef* SPIx, uint16_t *pTxBuffer, PollingEnable_t Polling)
{

	if(Polling == Polling_Enable)
	{
		while(!(SPIx->SR & (1 << TXE_FLAG)));
	}

	SPIx->DR = *pTxBuffer;

}

/**================================================================
 * @Fn				- MCAL_SPI_Receive
 * @brief 			- Retrieve the data from the SPI data register and put it on the pTxBuffer.
 * @param [in] 		- SPIx: where x can be (1 OR 2 depending on device used) to select the SPI peripheral
 * @param [in]		- pTxBuffer: A pointer to the receive buffer data.
 * @param [in]		- Polling: Parameter to check whether polling is enabled or not.
 * @retval 			- None
 * Note				- None
 */

void MCAL_SPI_Receive(SPI_TypeDef* SPIx, uint16_t *pRxBuffer, PollingEnable_t Polling)
{
	if(Polling == Polling_Enable)
	{
		while(!(SPIx->SR & (1 << RXNE_FLAG)));
	}

	*pRxBuffer = SPIx->DR;
}

void SPI1_IRQHandler(void)
{
	IRQ_SRC irq_src;

	irq_src.TXE = ((SPI1->SR & (1 << TXE_FLAG)) >> TXE_FLAG);
	irq_src.RXNE = ((SPI1->SR & (1 << RXNE_FLAG)) >> RXNE_FLAG);
	irq_src.ERR = ((SPI1->SR & (1 << OVR_FLAG)) >> OVR_FLAG) || ((SPI1->SR & (1 << MODF_FLAG)) >> MODF_FLAG);

	G_SPI_CONFIG[SPI1_IDX]->P_CallBack(irq_src);
}


void SPI2_IRQHandler(void)
{
	IRQ_SRC irq_src;

	irq_src.TXE = ((SPI2->SR & (1 << TXE_FLAG)) >> TXE_FLAG);
	irq_src.RXNE = ((SPI2->SR & (1 << RXNE_FLAG)) >> RXNE_FLAG);
	irq_src.ERR = ((SPI2->SR & (1 << OVR_FLAG)) >> OVR_FLAG) || ((SPI2->SR & (1 << MODF_FLAG)) >> MODF_FLAG);

	G_SPI_CONFIG[SPI2_IDX]->P_CallBack(irq_src);
}
