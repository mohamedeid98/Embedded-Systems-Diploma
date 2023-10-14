/*
 * lcd.c
 *
 *  Author: Mohamed Eid
 */ 

#include "../Inc/lcd.h"
#include "../../MCAL/Inc/timer2.h"


uint8_t firstCharAddr[] = {0x80, 0xC0, 0x94, 0xD4};
/****************************************************************************************
									LCD APIs Implementation
*****************************************************************************************/
/*void delay_us(uint32_t d)
{
	MCAL_TIM2_Delay_uS(d);
}
*/
/*
void MCAL_TIM2_Delay_uS(uint32_t t)
{
	uint32_t i,j;
	for(i=0 ; i<t ; i++)
		for(j=0 ; j<256 ; j++);
}

*/

void LCD_send_command(uint8_t cmnd)
{
#ifdef FOUR_LINE_MODE

	/****************************** send higher nibble to D4-D7 *************************************/
	MCAL_GPIO_WritePort(LCD_DATA, (MCAL_GPIO_ReadPort(LCD_DATA) & (~(0xF << SHIFT))) | ((((cmnd & 0xF0) >> 4) << SHIFT)));

	MCAL_GPIO_WritePin(LCD_CTRL, RS, GPIO_PIN_RESET);	// Clear to select command register.
	MCAL_GPIO_WritePin(LCD_CTRL, RW, GPIO_PIN_RESET);	// Clear for write operation.

	
	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_SET);
	MCAL_TIM2_Delay_uS(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_RESET);
	MCAL_TIM2_Delay_uS(100);
	
	/****************************** send low nibble to D4-D7 *************************************/
	MCAL_GPIO_WritePort(LCD_DATA, (MCAL_GPIO_ReadPort(LCD_DATA) & (~(0xF << SHIFT))) | (((cmnd & 0x0F) << SHIFT)));

	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_SET);
	MCAL_TIM2_Delay_uS(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_RESET);
	MCAL_TIM2_Delay_uS(100);

#endif	
	

}

/***********************************************************************************/

void LCD_send_data(uint8_t data)
{
	
#ifdef FOUR_LINE_MODE

	/****************************** send higher nibble to D4-D7 *************************************/
	MCAL_GPIO_WritePort(LCD_DATA, (MCAL_GPIO_ReadPort(LCD_DATA) & (~(0xF << SHIFT))) | ((((data & 0xF0) >> 4) << SHIFT)));

	MCAL_GPIO_WritePin(LCD_CTRL, RS, GPIO_PIN_SET);	// Set RS to select data register.
	MCAL_GPIO_WritePin(LCD_CTRL, RW, GPIO_PIN_RESET);	// Clear for write operation.

	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_SET);
	MCAL_TIM2_Delay_uS(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_RESET);
	MCAL_TIM2_Delay_uS(100);

	/****************************** send low nibble to D4-D7 *************************************/
	MCAL_GPIO_WritePort(LCD_DATA, (MCAL_GPIO_ReadPort(LCD_DATA) & (~(0xF << SHIFT))) | (((data & 0x0F) << SHIFT)));

	/* Set and reset EN for high to low pulse with delay to make enable wide. */
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_SET);
	MCAL_TIM2_Delay_uS(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_RESET);
	MCAL_TIM2_Delay_uS(100);



#endif
	

}

/**********************************************************************/
void LCD_Init()
{

	GPIO_PinConfig_t pinconfig;
	/* Configure the control port as output. */

	pinconfig.GPIO_PinNumber 	= RS;
	pinconfig.GPIO_PinMode   	= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber 	= RW;
	pinconfig.GPIO_PinMode   	= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber 	= EN;
	pinconfig.GPIO_PinMode   	= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);


	/* Configure the data port as output. */


	pinconfig.GPIO_PinNumber 	= D4;
	pinconfig.GPIO_PinMode   	= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber 	= D5;
	pinconfig.GPIO_PinMode   	= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber 	= D6;
	pinconfig.GPIO_PinMode   	= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber 	= D7;
	pinconfig.GPIO_PinMode   	= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(LCD_DATA, &pinconfig);



	
	
	/* 2- Disable the LCD to prevent any interruption */
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_RESET);

#ifdef FOUR_LINE_MODE
	LCD_send_command(0x33);
	LCD_send_command(0x32);
	LCD_send_command(TWO_LINE_FOUR_BIT_MODE);
#endif	

	LCD_send_command(DISPLAY_ON_CURSOR_OFF);				// Display ON, Cursor ON.
	LCD_send_command(CLEAR_DISPLAY_SCREEN);				// Clear LCD.
	
	MCAL_TIM2_Delay_uS(2000);										// Wait.
	LCD_send_command(SHIFT_CURSOR_RIGHT);				// Shift cursor right.

}

/****************************************************************************************************/
void LCD_gotoxy(uint8_t x, uint8_t y)
{
	LCD_send_command(firstCharAddr[y - 1] + x - 1);
	MCAL_TIM2_Delay_uS(100);
}

/****************************************************************************************************/

void LCD_print(uint8_t* str)
{
	uint8_t count = 0;
	
	while(*str)
	{
		/*if(count == 16)
		{
			LCD_gotoxy(1, 2);
		}
		else if(count == 32)
		{
			LCD_send_command(CLEAR_DISPLAY_SCREEN);
			MCAL_TIM2_Delay_uS(2000);
		}*/
		LCD_send_data(*str++);
		count++;
	}
}


void LCD_print_int_number(uint32_t num)
{
	uint8_t str[7];
	sprintf(str, "%ld", num);
	LCD_print((uint8_t*)str);
}





