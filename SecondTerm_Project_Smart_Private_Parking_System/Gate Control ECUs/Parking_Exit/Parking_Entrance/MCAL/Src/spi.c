/*
 * spi.c
 *
 *  Author: Mohamed	Eid
 */ 

/****************************************************************************************
										Includes 
*****************************************************************************************/
#include "../Inc/spi.h"

SPI_Config_t G_SPI_Config;
/****************************************************************************************
									Generic Functions 
*****************************************************************************************/
static void SPI_PinConfig()
{
	switch(G_SPI_Config.SS_Mode)
	{
		case SPI_SS_MODE_MATER_OUTPUT:
			DDRB |= (1 << SPI_SS);
			break;
		case SPI_SS_MODE_MATER_INPUT:
			DDRB &= ~(1 << SPI_SS);
			break;
		case SPI_SS_MODE_SLAVE_INPUT:
			DDRB &= ~(1 << SPI_SS);
			break;	
	}
	
	DDRB |= (1 << SPI_MOSI);
	DDRB &= ~(1 << SPI_MISO);
	if(G_SPI_Config.Mode == SPI_MODE_MASTER)
	{
		DDRB |= (1 << SPI_SCK);
	}
	else
	{
		DDRB &= ~(1 << SPI_SCK);
	}
}


/****************************************************************************************
										APIs 
*****************************************************************************************/
void MCAL_SPI_Init(SPI_Config_t* SPI_Config)
{
	G_SPI_Config = *SPI_Config;
	
	SPI_PinConfig();
	
	SPCR |= (SPI_Config->Mode) | (SPI_Config->First_Data_Transfer) | (SPI_Config->BaudRate_PreScaler) 
			| (SPI_Config->CLK_Polarity) | (SPI_Config->CLK_Phase) | (SPI_Config->INT_Mode);
			
	
	SPCR |= (1 << SPE);
}


void MCAL_SPI_Send(uint8_t TxBuffer)
{
	uint8_t flush_buffer;
	
	SPDR = TxBuffer;	/* Start transmission by writing the data on data register */
	
	while(!(SPSR & (1 << SPIF)));
	
	flush_buffer = SPDR;
	
}


void MCAL_SPI_Receive(uint8_t* pRxBuffer)
{
	if(G_SPI_Config.Mode == SPI_MODE_MASTER)
	{
		SPDR = 0xFF;
	}
	if(G_SPI_Config.Polling_Mode == SPI_POLLING_ENABLE)
	{
		while(!(SPSR & (1 << SPIF)));
	}
	*pRxBuffer = SPDR;
}

