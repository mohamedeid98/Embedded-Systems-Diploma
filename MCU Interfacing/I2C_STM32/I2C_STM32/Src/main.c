
#include "../MCAL/Inc/i2c.h"
#include "../HAL/EEPROM/eeprom.h"

int main(void)
{
	// Test Case 1
	uint8_t readBuffer[7] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
	uint8_t writeBuffer[7] = {0};
	uint8_t readBuffer2[7] = {0x8, 0x9, 0x1, 0x2, 0x3, 0x4, 0x5};
	uint8_t writeBuffer2[7] = {0};

	EEPROM_Init();
	EEPROM_Write_Nbytes(0xAF, readBuffer, 7);
	EEPROM_Read_Nbytes(0xAF, writeBuffer, 7);

	EEPROM_Write_Nbytes(0xAF, readBuffer2, 7);
	EEPROM_Read_Nbytes(0xAF, writeBuffer2, 7);

	while(1)
	{

	}

}
