/*
 * spi.h
 *
 *      Author: Mohamed Eid
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

/************************************************************************
								INCLUDES
*************************************************************************/
#include "gpio.h"


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
							Generic structs && enums
*************************************************************************/
typedef enum
{
	Polling_Enable,
	Polling_Disable
}PollingEnable_t;

typedef struct
{
	uint8_t TXE:1; 	// Tx buffer empty interrupt
	uint8_t RXNE:1; // Rx buffer not empty interrupt
	uint8_t ERR:1;   /* Error interrupt. The generation of an error condition occurs (CRCERR,
					   OVR, MODF in SPI mode and UDR, OVR in I2S mode).*/
	uint8_t Reserved:5;
}IRQ_SRC;

/************************************************************************
						 Configuration Structure
*************************************************************************/

typedef struct
{
	uint16_t Mode;					// Specifies the configuration of SPI as master or slave.
									// This parameter must be set based on the @ref Mode_define

	uint16_t Communication_Mode; 	// This parameter must be set based on the @ref COMM_MODE_define

	uint16_t Frame_Size;			// Specifies the data frame format 8/16 bits.
									// This parameter must be set based on the @ref Frame_Size_define

	uint16_t Frame_Format;			// Determine which bit is set first the MSB or LSB.
									// This parameter must be set based on the @ref DFF_define

	uint16_t BaudRate_PreScaler; 	// Specifies the pre-scaler the clock will be divided on.
									// This parameter must be set based on the @ref BR_define

	uint16_t CLK_Polarity;          // Specifies the steady state value of the clock.
									// This parameter must be set based on the @ref CPOL_define

	uint16_t CLK_Phase;				// Specifies where to sample the data on master and slave.
									// This parameter must be set based on @ref CPHA_define.

	uint16_t INT_Enable;			// Enable the desired interrupt signals.
									// This parameter must be set based on the @ref INT_EN_define

	uint16_t NSS_MODE;				// Specifies the mode of the slave select pin.
									// This parameter must be set based on the @ref NSS_MODE_define

	//TODO The pointer to the call back function.
	void (*P_CallBack)(IRQ_SRC );

}SPI_Config_t;





/************************************************************************
							Reference Macros
*************************************************************************/

// @ref Mode_define

/* Bit 2 MSTR: Master selection
		  0: Slave configuration
		  1: Master configuration */

#define SPI_MODE_MASTER								(0x1U << 2)
#define SPI_MODE_SLAVE								(0x00000000U)


// @ref COMM_MODE_define

// Full Duplex Mode
#define SPI_COMM_MODE_FULL_DUPLEX					(0x00000000U)
#define SPI_COMM_MODE_FULL_DUPLEX_Rx_ONLY			(0x1U << 10)

//TODO
// Half Duplex Mode
#define SPI_COMM_MODE_HALF_DUPLEX_Rx_ONLY  			(0x1U << 15)
#define SPI_COMM_MODE_HALF_DUPLEX_Tx_ONLY  			(0x1U << 15) | (0x1U << 14)


// @ref Frame_Size_define

#define SPI_FRAME_SIZE_8bits 						(0x00000000U)
#define SPI_FRAME_SIZE_16bits 						(0x1U << 11)

// @ref DFF_define
#define SPI_DFF_MSB									(0x00000000U)
#define SPI_DFF_LSB									(0x1U << 7)

// @ref BR_define

/* Bits 5:3 BR[2:0]: Baud rate control
			 000: fPCLK/2
			 001: fPCLK/4
			 010: fPCLK/8
			 011: fPCLK/16
			 100: fPCLK/32
			 101: fPCLK/64
			 110: fPCLK/128
			 111: fPCLK/256 */

#define SPI_BR_fPCLK_2								(0x00000000U)
#define SPI_BR_fPCLK_4								(0b001U << 3)
#define SPI_BR_fPCLK_8								(0b010U << 3)
#define SPI_BR_fPCLK_16								(0b011U << 3)
#define SPI_BR_fPCLK_32								(0b100U << 3)
#define SPI_BR_fPCLK_64								(0b101U << 3)
#define SPI_BR_fPCLK_128							(0b110U << 3)
#define SPI_BR_fPCLK_256							(0b111U << 3)



// @ref CPOL_define

#define SPI_CPOL_IDLE_LOW                           (0x00000000U)
#define SPI_CPOL_IDLE_HIGH                          (0x1U << 1)

// @ref CPHA_define

#define SPI_CPHA_1ST_EDGE							(0x00000000U)
#define SPI_CPHA_2ND_EDGE							(0x1U << 0)

// @ref INT_EN_define
// NOTE Here we are dealing with SPI_CR2 register
#define SPI_INT_EN_TXEIE							(uint32_t)(1 << 7)
#define SPI_INT_EN_RXNEIE							(uint32_t)(1 << 6)
#define SPI_INT_EN_ERRIE							(uint32_t)(1 << 5)
#define SPI_INT_DISABLE								(uint32_t)(0)


// @ref NSS_MODE_define


// Driven by hardware
#define SPI_NSS_MODE_SLAVE_HW						(uint32_t)(0) 					 // SPI_CR2
#define SPI_NSS_MODE_MASTER_HW_OUTPUT				(uint32_t)(1 << 2) 				 // SPI_CR2
#define SPI_NSS_MODE_MASTER_HW_INPUT				(uint32_t)(0) 	  				 // SPI_CR2
// Driven by software
#define SPI_NSS_MODE_SW_RESET						(uint32_t)(1 << 9) 				 // SPI_CR1
#define SPI_NSS_MODE_SW_SET							(uint32_t)(1 << 9) | (1 << 8)    // SPI_CR1


/************************************************************************
								  APIs
*************************************************************************/


void MCAL_SPI_Init(SPI_TypeDef* SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx);

uint8_t MCAL_SPI_Send(SPI_TypeDef* SPIx, uint8_t pTxBuffer, PollingEnable_t Polling);
void MCAL_SPI_Receive(SPI_TypeDef* SPIx, uint8_t *pRxBuffer, PollingEnable_t Polling);








#endif /* INC_SPI_H_ */
