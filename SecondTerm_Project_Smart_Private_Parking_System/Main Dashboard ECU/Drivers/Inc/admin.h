/*
 * admin.h
 *
 *      Author: Mohamed Eid
 */

#ifndef ADMIN_H_
#define ADMIN_H_

#include "../STM32F103C6_Drivers/MCAL/Inc/exti.h"
#include "../STM32F103C6_Drivers/MCAL/Inc/uart.h"

#include "../STM32F103C6_Drivers/MCAL/Inc/timer2.h"
#include "../STM32F103C6_Drivers/HAL/Inc/spi_eeprom.h"
#include "../STM32F103C6_Drivers/HAL/Inc/keypad.h"
#include "../STM32F103C6_Drivers/HAL/Inc/lcd.h"
#include "../STM32F103C6_Drivers/HAL/Inc/lcd.h"
#include "../STM32F103C6_Drivers/HAL/Inc/7seg.h"


void ADMIN_Init(void);
void ADMIN_Add_IDs(void);
void ADMIN_Delete_Entire_IDs(void);
void ADMIN_Delete_ID(void); //TODO
void ADMIN_Display_IDs(void);
void ADMIN_Check_Password(void);


#endif /* ADMIN_H_ */
