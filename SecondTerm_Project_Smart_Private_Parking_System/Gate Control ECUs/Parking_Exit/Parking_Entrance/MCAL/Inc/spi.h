/*
 * spi.h
 *
 *  @Author: Mohamed Eid
 */ 


#ifndef SPI_H_
#define SPI_H_

/****************************************************************************************
										Includes 
*****************************************************************************************/
#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>
#include<stdio.h>


/****************************************************************************************
										SPI_PINS 
*****************************************************************************************/
#define SPI_SS				4
#define SPI_MOSI			5
#define SPI_MISO			6
#define SPI_SCK				7


/****************************************************************************************
								 Configuration Structure 
*****************************************************************************************/
typedef struct 
{
	uint8_t Mode;					/* Specifies the mode of the SPI (Master/Slave).			*/
									/* This parameter can be a value of @ref SPI_MODE_define	*/
	
	uint8_t First_Data_Transfer;	/* Specifies LSB First or MSB First Data Transfer			*/
									/* This parameter can be a value of @ref SPI_FDT_define		*/
	
	uint8_t BaudRate_PreScaler;		/* Specifies the pre-scaler the clock will be divided on.	*/
									/* This parameter can be a value of @ref SPI_BR_define		*/
									
	uint8_t CLK_Polarity;			/* Specifies the steady state value of the clock.			*/
									/* This parameter can be a value of @ref SPI_CPOL_define	*/	
									
	uint8_t CLK_Phase;				/* Specifies where to sample the data on master and slave.	*/
									/* This parameter must be set based on @ref SPI_CPHA_define.*/

	uint8_t SS_Mode;				/* Specifies the function of the SS pin						*/
									/* This parameter can be a value of @ref SPI_SS_MODE_define */
	
	uint8_t INT_Mode;				/* Specifies the interrupt mode(enable/disable).            */
									/* This parameter can be a value of @ref SPI_INT_define		*/	
	
	uint8_t Polling_Mode;			/* Specifies whether to poll for the flags or not			*/
									/* This parameter can be a value of @ref SPI_POLLING_define */
}SPI_Config_t;



/****************************************************************************************
								 Reference Macros 
*****************************************************************************************/

/* @ref SPI_MODE_define */
#define SPI_MODE_MASTER				(1 << MSTR)
#define SPI_MODE_SLAVE				((uint8_t)0x00)

/* @ref SPI_FDT_define */
#define SPI_FDT_MSB					((uint8_t)0x00)	
#define SPI_FDT_LSB					(1 << DORD)

/* @ref SPI_BR_define */
#define SPI_BR_Fosc_4				((uint8_t)0x00)
#define SPI_BR_Fosc_16				((uint8_t)0x01)
#define SPI_BR_Fosc_64				((uint8_t)0x02)
#define SPI_BR_Fosc_128				((uint8_t)0x03)

/* @ref SPI_CPOL_define */
#define SPI_CPOL_IDLE_LOW			((uint8_t)0x00)
#define SPI_CPOL_IDLE_HIGH			(1 << CPOL)

/* @ref SPI_CPHA_define */
#define SPI_CPHA_1ST_EDGE			((uint8_t)0x00)
#define SPI_CPHA_2ND_EDGE			(1 << CPHA)

/* @ref SPI_SS_MODE_define */
#define SPI_SS_MODE_MATER_OUTPUT	((uint8_t)0x00)
#define SPI_SS_MODE_MATER_INPUT		((uint8_t)0x01)
#define SPI_SS_MODE_SLAVE_INPUT		((uint8_t)0x03)

/* @ref SPI_INT_define */
#define SPI_INT_ENABLE				(1 << SPIE)
#define SPI_INT_DISABLE				((uint8_t)0x00)

/* @ref SPI_POLLING_define */
enum
{
	SPI_POLLING_DISABLE=0,
	SPI_POLLING_ENABLE=1
};
/****************************************************************************************
										APIs 
*****************************************************************************************/
void MCAL_SPI_Init(SPI_Config_t* SPI_Config);
void MCAL_SPI_Send(uint8_t TxBuffer);
void MCAL_SPI_Receive(uint8_t* pRxBuffer);




#endif /* SPI_H_ */