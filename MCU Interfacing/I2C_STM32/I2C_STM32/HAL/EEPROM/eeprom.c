/*
 * eeprom.c
 *
 *      Author: Mohamed Eid
 */


#include "eeprom.h"


void EEPROM_Init(void)
{
	/* Configure I2C controller to act as a master */

	I2C_Config_t I2C_CFG;

	I2C_CFG.I2C_ACK_Control = I2C_ACK_ENABLE;
	I2C_CFG.I2C_ClockSpeed = I2C_CLOCK_SM_100K;
	I2C_CFG.I2C_Mode = I2C_MODE_ENABLE;
	I2C_CFG.P_Slave_Event_CallBack = NULL;
	I2C_CFG.Stretch_Mode = I2C_NOSTRETCH_MODE_DISABLE;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C_CFG);

}




unsigned char EEPROM_Write_Nbytes(uint32_t Memory_Address, uint8_t* bytes, uint8_t data_len)
{
	int i;
	static uint8_t buffer[256];

	buffer[0] = (uint8_t)(Memory_Address >> 8);
	buffer[1] = (uint8_t)Memory_Address;

	for (i = 2 ; i < (data_len+2) ; i++)
	{
		buffer[i] = bytes[i-2];
	}

	MCAL_I2C_Master_Tx(I2C1, EEPROM_ADDRESS, buffer, (data_len + 2), stopEnable, start);

	return 0;
}


unsigned char EEPROM_Read_Nbytes(uint32_t Memory_Address, uint8_t* bytes, uint8_t data_len)
{
	static uint8_t buffer[2];

	buffer[0] = (uint8_t)(Memory_Address >> 8);
	buffer[1] = (uint8_t)Memory_Address;

	MCAL_I2C_Master_Tx(I2C1, EEPROM_ADDRESS, buffer,  2, stopDisable, start);
	MCAL_I2C_Master_Rx(I2C1, EEPROM_ADDRESS, bytes,  data_len, stopEnable, repeated_start);

	return 0;
}


