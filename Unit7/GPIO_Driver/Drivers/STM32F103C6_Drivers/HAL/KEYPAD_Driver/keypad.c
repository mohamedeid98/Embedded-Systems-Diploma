/*
 * keypad.c
 *
 * Created: 6/25/2023 9:30:48 AM
 *  Author: Mohamed Eid
 *
 */

#include "keypad.h"


int keypad_row[] = {R0, R1, R2 ,R3};
int keypad_col[] = {C0, C1, C2 ,C3};

void keypad_init()
{
	GPIO_PinConfig_t pinconfig;

	pinconfig.GPIO_PinNumber = R0;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber = R1;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber = R2;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber = R3;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber = C0;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber = C1;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber = C2;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber = C3;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);


	MCAL_GPIO_WritePort(KEYPAD_PORT, ((KEYPAD_PORT->ODR & 0xFF00) | 0xFF << PORT_SHIFT));

}



char keypad_getkey()
{
	int i, j;
	for(i = 0 ; i < 4 ; i++)
	{

		MCAL_GPIO_WritePin(KEYPAD_PORT, C0, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C1, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C2, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, C3, GPIO_PIN_SET);

		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_col[i], GPIO_PIN_RESET);

	/*	KEYPAD_PORT |= ((1 << keypad_col[0]) | (1 << keypad_col[1]) | (1 << keypad_col[2]) | (1 << keypad_col[3])) ;
		KEYPAD_PORT &= ~(1 << keypad_col[i]);
*/
		for(j = 0 ; j < 4 ; j++)
		{
			if(!(MCAL_GPIO_ReadPin(KEYPAD_PORT, keypad_row[j])))
			{
				while(!(MCAL_GPIO_ReadPin(KEYPAD_PORT, keypad_row[j])));
				switch(i)
				{
				case 0:
					if(j == 0)		return '7';
					else if(j == 1)	return '4';
					else if(j == 2)	return '1';
					else if(j == 3)	return '?';
					break;

				case 1:
					if(j == 0)		return '8';
					else if(j == 1)	return '5';
					else if(j == 2)	return '2';
					else if(j == 3)	return '0';
					break;


				case 2:
					if(j == 0)		return '9';
					else if(j == 1)	return '6';
					else if(j == 2)	return '3';
					else if(j == 3)	return '=';
					break;


				case 3:
					if(j == 0)		return '/';
					else if(j == 1)	return '*';
					else if(j == 2)	return '-';
					else if(j == 3)	return '+';
					break;


				}
			}
		}
	}
	return 'A';	
}

