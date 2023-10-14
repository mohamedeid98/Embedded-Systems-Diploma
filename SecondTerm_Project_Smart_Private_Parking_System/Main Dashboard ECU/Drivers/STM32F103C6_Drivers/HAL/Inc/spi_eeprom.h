/*
 * spi_eeprom.h
 *
 *      Author: Mohamed Eid
 */

#ifndef HAL_INC_SPI_EEPROM_H_
#define HAL_INC_SPI_EEPROM_H_

/********************************************************************************************
 * 										Includes
 ********************************************************************************************/
#include "../../MCAL/Inc/spi.h"
#include "../../MCAL/Inc/timer2.h"

/********************************************************************************************
 * 									Generic Macros
 ********************************************************************************************/
#define SS_PIN					GPIO_PIN4
#define SS_PORT					GPIOA


/********************************************************************************************
 * 									Instruction Set
 ********************************************************************************************/

typedef enum
{
	SPI_EEPROM_WRSR  = 1,  			/* Write STATUS register 										*/
	SPI_EEPROM_WRITE = 2, 			/* Write data to memory array beginning at selected address 	*/
	SPI_EEPROM_READ  = 3,			/* Read data from memory array beginning at selected address 	*/
	SPI_EEPROM_WRDI  = 4,			/* Reset the write enable latch (disable write operations)		*/
	SPI_EEPROM_RDSR	 = 5,			/* Read STATUS register											*/
	SPI_EEPROM_WREN	 = 6			/* Set the write enable latch (enable write operations)         */

}InstructionTypedef;



/********************************************************************************************
 * 									     APIs
 ********************************************************************************************/
void HAL_SPI_EEPROM_Init(SPI_TypeDef* SPIx);
void HAL_SPI_EEPROM_Read(SPI_TypeDef* SPIx, uint16_t address, uint8_t* pReadBuffer, uint8_t size);
void HAL_SPI_EEPROM_Write(SPI_TypeDef* SPIx, uint16_t address, uint8_t* pWriteBuffer, uint8_t size);
uint8_t HAL_SPI_EEPROM_ReadSR(void);



#endif /* HAL_INC_SPI_EEPROM_H_ */
