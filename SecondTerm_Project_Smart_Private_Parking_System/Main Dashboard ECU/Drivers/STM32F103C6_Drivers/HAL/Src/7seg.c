/*
 * 7seg.c
 *
 *      Author: Mohamed Eid
 */


/********************************************************************************************
* 										Includes
 ********************************************************************************************/
#include "../Inc/7seg.h"


/********************************************************************************************
* 									APIs Implementation
 ********************************************************************************************/

void HAL_7SEG_Init(void)
{
	GPIO_PinConfig_t pinconfig;

	pinconfig.GPIO_PinMode 		= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	pinconfig.GPIO_PinNumber	= SEVEN_SEGMENT_PIN1;
	MCAL_GPIO_Init(SEVEN_SEGMENT_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber	= SEVEN_SEGMENT_PIN2;
	MCAL_GPIO_Init(SEVEN_SEGMENT_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber	= SEVEN_SEGMENT_PIN3;
	MCAL_GPIO_Init(SEVEN_SEGMENT_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber	= SEVEN_SEGMENT_PIN4;
	MCAL_GPIO_Init(SEVEN_SEGMENT_PORT, &pinconfig);

	MCAL_GPIO_WritePort(SEVEN_SEGMENT_PORT, (MCAL_GPIO_ReadPort(SEVEN_SEGMENT_PORT) & (~(0xF << PIN_SHIFT))));
}

void HAL_7SEG_Update(uint8_t val)
{

	MCAL_GPIO_WritePort(SEVEN_SEGMENT_PORT, ( ( MCAL_GPIO_ReadPort(SEVEN_SEGMENT_PORT) & (~(0xF << PIN_SHIFT)) ) | ((val & 0xF) << PIN_SHIFT))  );

}

void HAL_7SEG_Reset(void)
{
	MCAL_GPIO_WritePort(SEVEN_SEGMENT_PORT, (MCAL_GPIO_ReadPort(SEVEN_SEGMENT_PORT) & (~(0xF << PIN_SHIFT))));
}
