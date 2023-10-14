/*
 * keypad.c
 *
 *      Author: Mohamed Eid
 */

#include "../Inc/keypad.h"

uint8_t keypad[4][4] = {

		/*{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'?', '0', '=', '+'}*/
		{ '*' , 0 , '#' },
		{ 7 , 8 , 9 },
		{ 4 , 5 , 6 },
		{ 1 , 2 , 3 }
};

uint32_t Keypad_Raws[4] = {R1, R2, R3, R4};
uint32_t Keypad_Col[3] = {C1, C2, C3};

void HAL_Keypad_Init(void)
{
	/* Configure keypad raws as output open drain */
	GPIO_PinConfig_t pincofig;

	pincofig.GPIO_PinMode		= GPIO_MODE_OUTPUT_PP;
	pincofig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	pincofig.GPIO_PinNumber		= R1;
	MCAL_GPIO_Init(KEYPAD_OUPUT, &pincofig);

	pincofig.GPIO_PinNumber		= R2;
	MCAL_GPIO_Init(KEYPAD_OUPUT, &pincofig);

	pincofig.GPIO_PinNumber		= R3;
	MCAL_GPIO_Init(KEYPAD_OUPUT, &pincofig);

	pincofig.GPIO_PinNumber		= R4;
	MCAL_GPIO_Init(KEYPAD_OUPUT, &pincofig);

	/******************************************************************************************/
						/* Configure keypad columns as pull down. */

	pincofig.GPIO_PinMode		= GPIO_MODE_INPUT_PD;

	pincofig.GPIO_PinNumber		= C1;
	MCAL_GPIO_Init(KEYPAD_INPUT, &pincofig);

	pincofig.GPIO_PinNumber		= C2;
	MCAL_GPIO_Init(KEYPAD_INPUT, &pincofig);

	pincofig.GPIO_PinNumber		= C3;
	MCAL_GPIO_Init(KEYPAD_INPUT, &pincofig);


	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R1, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R2, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R3, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R4, GPIO_PIN_RESET);

}


uint8_t HAL_Keypad_GetKey()
{
	uint8_t i, j, key='#';

	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R1, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R2, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R3, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(KEYPAD_OUPUT, R4, GPIO_PIN_RESET);

	for(i = 0 ; i < 4 ; i++)
	{

		MCAL_TIM2_Delay_mS(10);
		MCAL_GPIO_WritePin(KEYPAD_OUPUT, Keypad_Raws[i], GPIO_PIN_SET);

		for(j = 0 ; j < 3 ; j++)
		{
			if((MCAL_GPIO_ReadPin(KEYPAD_INPUT, Keypad_Col[j])))
			{

				while((MCAL_GPIO_ReadPin(KEYPAD_INPUT, Keypad_Col[j])));
				key = keypad[i][j];
				MCAL_GPIO_WritePin(KEYPAD_OUPUT, Keypad_Raws[i], GPIO_PIN_RESET);
				break;
			}

		}
		MCAL_GPIO_WritePin(KEYPAD_OUPUT, Keypad_Raws[i], GPIO_PIN_RESET);

	}
	return key;
}












