/*
 * eeprom.h
 *
 *      Author: Mohamed Eid
 */

#ifndef EEPROM_EEPROM_H_
#define EEPROM_EEPROM_H_

#include "../../MCAL/Inc/i2c.h"

#define EEPROM_ADDRESS		0x2A


void EEPROM_Init(void);

unsigned char EEPROM_Write_Nbytes(uint32_t Memory_Address, uint8_t* bytes, uint8_t data_len);
unsigned char EEPROM_Read_Nbytes(uint32_t Memory_Address, uint8_t* bytes, uint8_t data_len);



#endif /* EEPROM_EEPROM_H_ */
