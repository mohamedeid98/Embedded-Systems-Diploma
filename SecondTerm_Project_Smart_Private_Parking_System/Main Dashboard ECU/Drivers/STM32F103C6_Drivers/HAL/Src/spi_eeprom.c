/*
 * spi_eeprom.c
 *
 *      Author: Mohamed Eid
 */


/********************************************************************************************
 * 										Includes
 ********************************************************************************************/

#include "../Inc/spi_eeprom.h"



uint8_t HAL_SPI_EEPROM_ReadSR()
{
	uint8_t data=0;

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_RESET);
	MCAL_SPI_Send(SPI1, SPI_EEPROM_RDSR, Polling_Enable);	 // Send write enable instruction.

	MCAL_SPI_Receive(SPI1, &data, Polling_Enable);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_SET);

	return (uint8_t)data;
}


/********************************************************************************************
* 									APIs Implementation
 ********************************************************************************************/

void HAL_SPI_EEPROM_Init(SPI_TypeDef* SPIx)
{
	/************************** SPIx Configuration ****************************************/
	SPI_Config_t spi_config;

	spi_config.Mode 				= SPI_MODE_MASTER;
	spi_config.Communication_Mode	= SPI_COMM_MODE_FULL_DUPLEX;
	spi_config.Frame_Size			= SPI_FRAME_SIZE_8bits;
	spi_config.Frame_Format			= SPI_DFF_MSB;
	spi_config.BaudRate_PreScaler	= SPI_BR_fPCLK_8;
	spi_config.CLK_Polarity			= SPI_CPOL_IDLE_LOW;
	spi_config.CLK_Phase			= SPI_CPHA_1ST_EDGE;
	spi_config.NSS_MODE				= SPI_NSS_MODE_SW_SET;
	spi_config.INT_Enable			= SPI_INT_DISABLE;
	spi_config.P_CallBack			= NULL;

	MCAL_SPI_Init(SPIx, &spi_config);

	/************************** Slave Select pin (SS) Configuration ************************/

	/* Configured as general output push pull */

	GPIO_PinConfig_t pinconfig;

	pinconfig.GPIO_PinMode		= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_PinNumber	= SS_PIN;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(SS_PORT, &pinconfig);

	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_SET);

	MCAL_TIM2_Delay_mS(10);

	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_RESET); // Clear the slave select pin to start sending.
	MCAL_SPI_Send(SPIx, SPI_EEPROM_WRDI, Polling_Enable);	 // Send write enable instruction.
	MCAL_TIM2_Delay_uS(5);
	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_SET); 	 // Set the slave select pin.

	while((HAL_SPI_EEPROM_ReadSR() & (1 << 0)));


}



void HAL_SPI_EEPROM_Write(SPI_TypeDef* SPIx, uint16_t address, uint8_t* pWriteBuffer, uint8_t size)
{
	uint8_t i;
	uint8_t Bytes[66];

	Bytes[0] = ((uint8_t)(address >> 8));
	Bytes[1] = ((uint8_t)address);

	for(i = 2 ; i < (size+2) ; i++)
	{
		Bytes[i] = pWriteBuffer[i-2];
	}

	/* WRITE ENABLE SEQUENCE (WREN) to enable the write operation */

	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_RESET); // Clear the slave select pin to start sending.
	MCAL_SPI_Send(SPIx, SPI_EEPROM_WREN, Polling_Enable);	 // Send write enable instruction.
	MCAL_TIM2_Delay_uS(5);
	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_SET); 	 // Set the slave select pin.
	while((HAL_SPI_EEPROM_ReadSR() & (1 << 0)));


	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_RESET); // Clear the slave select pin to start sending.
	MCAL_SPI_Send(SPIx, SPI_EEPROM_WRITE, Polling_Enable);	 // Send write enable instruction.


	for (i = 0 ; i < (size+2) ; i++)
	{
		MCAL_SPI_Send(SPIx, Bytes[i], Polling_Enable);

	}

	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_SET); 	 // Set the slave select pin.

	while((HAL_SPI_EEPROM_ReadSR() & (1 << 0)));

}


void HAL_SPI_EEPROM_Read(SPI_TypeDef* SPIx, uint16_t address, uint8_t* pReadBuffer, uint8_t size)
{
	uint8_t i;
	uint8_t instruction_address[3] = {0};
	instruction_address[0] = (SPI_EEPROM_READ);
	instruction_address[1] = ((uint8_t)(address >> 8));
	instruction_address[2] = ((uint8_t)address);

	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_RESET); // Clear the slave select pin to start sending.

	for(i = 0 ; i < 3 ; i++)
	{
		MCAL_SPI_Send(SPIx, instruction_address[i], Polling_Enable);

	}

	for(i = 0 ; i < size ; i++)
	{
		MCAL_SPI_Receive(SPIx, (pReadBuffer++), Polling_Enable);


	}

	MCAL_GPIO_WritePin(SS_PORT, SS_PIN, GPIO_PIN_SET); 	 // Set the slave select pin.

}
















