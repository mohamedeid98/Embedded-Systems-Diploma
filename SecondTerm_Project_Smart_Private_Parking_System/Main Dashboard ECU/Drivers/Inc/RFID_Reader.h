/*
 * RFID_Reader.h
 *
 *      Author: Mohamed Eid
 */

#ifndef RFID_READER_H_
#define RFID_READER_H_

#include "../STM32F103C6_Drivers/MCAL/Inc/spi.h"
#include "../STM32F103C6_Drivers/HAL/Inc/7seg.h"
#include "../STM32F103C6_Drivers/MCAL/Inc/uart.h"



void RFID_Init(void);
void RFID_Entrance_Reader(void);
void RFID_Exit_Reader(void);

#endif /* RFID_READER_H_ */
