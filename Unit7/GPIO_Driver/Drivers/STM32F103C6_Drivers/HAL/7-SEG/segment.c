/*
 * segment.c
 *
 *  Created on: Jul 5, 2023
 *      Author: Mohamed
 */


#include "segment.h"

void Segment_Init()
{
	// Configure the 7 Layers pins as output pins
		GPIO_PinConfig_t* PinConfig = NULL;

		PinConfig->GPIO_PinNumber = SEGMENT_PIN1;
		PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		PinConfig->GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(SEGMENT_PORT, PinConfig);

		PinConfig->GPIO_PinNumber = SEGMENT_PIN2;
		PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		PinConfig->GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(SEGMENT_PORT, PinConfig);

		PinConfig->GPIO_PinNumber = SEGMENT_PIN3;
		PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		PinConfig->GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(SEGMENT_PORT, PinConfig);

		PinConfig->GPIO_PinNumber = SEGMENT_PIN4;
		PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		PinConfig->GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(SEGMENT_PORT, PinConfig);

		PinConfig->GPIO_PinNumber = SEGMENT_PIN5;
		PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		PinConfig->GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(SEGMENT_PORT, PinConfig);

		PinConfig->GPIO_PinNumber = SEGMENT_PIN6;
		PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		PinConfig->GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(SEGMENT_PORT, PinConfig);

		PinConfig->GPIO_PinNumber = SEGMENT_PIN7;
		PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
		PinConfig->GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(SEGMENT_PORT, PinConfig);
}
