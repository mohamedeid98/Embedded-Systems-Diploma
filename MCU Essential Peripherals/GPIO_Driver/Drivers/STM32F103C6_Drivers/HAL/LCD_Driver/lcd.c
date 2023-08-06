/*
 * lcd.c
 *
 * Created: 6/25/2023 9:26:59 AM
 *  Author: Mohamed Eid
 */ 

#include "lcd.h"



void _delay_ms(uint32_t m_sec)
{
	for(int i = 0 ; i < m_sec ; i++)
	{
		for(int j = 0 ; j < 255 ; j++);
	}
}

void LCD_init()
{
	_delay_ms(20);

	GPIO_PinConfig_t pinconfig;

	pinconfig.GPIO_PinNumber = RS;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = RW;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = EN;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);



#ifdef EIGHT_BIT_MODE

	pinconfig.GPIO_PinNumber = GPIO_PIN0;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN1;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN2;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN3;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN4;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN5;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN6;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN7;
	pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_DATA, &pinconfig);

 	_delay_ms(15);

	LCD_send_command(CLEAR_DISPLAY);
	LCD_send_command(FUNCTION_SET_8_BIT_MODE);

#endif

#ifdef FOUR_BIT_MODE
	LCD_DATA_DIR |= (0xFF << DATA_SHIFT);
	LCD_send_command(0x02); //Sets to 4-bit operation. In this case, operation is handled as 8 bits by initialization, and only this instruction completes with one write.8

	LCD_send_command(FUNCTION_SET_4_BIT_MODE);

#endif

	LCD_send_command(ENTRY_MODE_SET);
	LCD_send_command(0x01); //
	LCD_send_command(DISPLAY_ON_OFF_CONTROL);
	LCD_send_command(0x80);
}


void LCD_send_command(uint8_t command)
{
	MCAL_GPIO_WritePin(LCD_CTRL, RS, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW, GPIO_PIN_RESET);

 	_delay_ms(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_SET);
 	_delay_ms(1);

#ifdef EIGHT_BIT_MODE


	MCAL_GPIO_WritePort(LCD_DATA, ((MCAL_GPIO_ReadPort(LCD_DATA) & 0xFF00) | command));
	_delay_ms(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_RESET);
 	_delay_ms(1);


#endif

#ifdef FOUR_BIT_MODE

	LCD_DATA = ((LCD_DATA & 0x0F) | (command & 0xF0));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);


	LCD_DATA = ((LCD_DATA & 0x0F) | (command << 4));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);


#endif
}



void LCD_write_char(uint8_t character)
{

#ifdef EIGHT_BIT_MODE
	MCAL_GPIO_WritePin(LCD_CTRL, RS, GPIO_PIN_SET);
 	MCAL_GPIO_WritePin(LCD_CTRL, RW, GPIO_PIN_RESET);
 	_delay_ms(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_SET);
 	_delay_ms(1);
	MCAL_GPIO_WritePort(LCD_DATA, ((MCAL_GPIO_ReadPort(LCD_DATA) & 0xFF00) | character));

	_delay_ms(1);
	MCAL_GPIO_WritePin(LCD_CTRL, EN, GPIO_PIN_RESET);

	_delay_ms(1);


#endif

#ifdef FOUR_BIT_MODE
	LCD_CTRL |= (1 << RS);
	LCD_CTRL &= ~(1 << RW);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);

	LCD_DATA = ((LCD_DATA & 0x0F) | (character & 0xF0));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);
	LCD_CTRL |= (1 << EN);
	_delay_ms(1);



	LCD_DATA = ((LCD_DATA & 0x0F) | (character << 4));
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN);
	_delay_ms(1);

#endif

}

void LCD_set_DDRAM_ADD(uint8_t position)
{
	LCD_send_command(position);
}



void LCD_write_string(char *string)
{
	int counter=0;
	while(*string > 0)
	{

		LCD_write_char(*string++);
		counter++;
		if(counter == 16)
		{
			LCD_send_command(SET_DDRAM_BEGIN_LINE2);
		}
		else if(counter == 32 || counter ==33)
		{
			LCD_send_command(CLEAR_DISPLAY);
			LCD_send_command(SET_DDRAM_BEGIN_LINE1);
			counter = 0;
		}


	}
}


void LCD_display_number(int number)
{
	char str[7];
	sprintf(str, "%d", number);
	LCD_write_string(str);
}


void LCD_clear_display()
{
	LCD_send_command(CLEAR_DISPLAY);
}

void LCD_display_real_number(double number)
{
	char str[16];

	char *tmpSign = (number < 0) ? "-" : "";
	float tmpVal = (number < 0) ? -number : number;
	int tmpInt1 = tmpVal ;
	float tmpFrac = tmpVal - tmpInt1;
	int tmpInt2 = tmpFrac * 10000;
	sprintf(str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);

	LCD_write_string(str);
}
