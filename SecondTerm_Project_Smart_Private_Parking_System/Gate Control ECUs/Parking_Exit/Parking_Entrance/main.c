/*
 *
 * Author : Mohamed Eid
 */ 
#include "HAL/Inc/lcd.h"
#include "MCAL/Inc/spi.h"
#include "HAL/Inc/servo.h"
#include "HAL/Inc/led.h"
#include "HAL/Inc/pir.h"

#include<avr/interrupt.h>

#define RLED_PIN    0
#define GLED_PIN	1

uint8_t rData, flag, servo;

void lcd_default_msg()
{	
	HAL_LCD_send_command(CLEAR_DISPLAY_SCREEN);
	_delay_ms(10);
	HAL_LCD_print("WELCOME!");
	HAL_LCD_gotoxy(1, 2);
	HAL_LCD_print("Scan your ID card!");

}

void lcd_authorized_msg()
{
	HAL_LCD_send_command(CLEAR_DISPLAY_SCREEN);
	_delay_ms(10);
	HAL_LCD_print("Authorized");
	HAL_LCD_gotoxy(1, 2);
	HAL_LCD_print("Gate Open!");

}

void lcd_unauthorized_msg()
{
	HAL_LCD_send_command(CLEAR_DISPLAY_SCREEN);
	_delay_ms(10);
	HAL_LCD_print("UnAuthorized");
	HAL_LCD_gotoxy(1, 2);
	HAL_LCD_print("Scan valid ID!");

}

void lcd_NOavailable_slots_msg()
{
	HAL_LCD_send_command(CLEAR_DISPLAY_SCREEN);
	_delay_ms(10);
	HAL_LCD_print("No Available Slots");
}

void flah_gled()
{
	HAL_LED_ON(&PORTD, GLED_PIN);
	_delay_ms(500);
	HAL_LED_OFF(&PORTD, GLED_PIN);
}

void flah_rled()
{
	HAL_LED_ON(&PORTD, RLED_PIN);
	_delay_ms(100);
	HAL_LED_OFF(&PORTD, RLED_PIN);
	_delay_ms(100);
	HAL_LED_ON(&PORTD, RLED_PIN);
	_delay_ms(100);
	HAL_LED_OFF(&PORTD, RLED_PIN);
	_delay_ms(100);
	HAL_LED_ON(&PORTD, RLED_PIN);
	_delay_ms(100);
	HAL_LED_OFF(&PORTD, RLED_PIN);
}

void GateAction(uint8_t command)
{
	switch(command)
	{
		case 1:
			flag=1;
			lcd_authorized_msg();
			HAL_Servo_Update(5);
		break;
		
		case 2:
			lcd_unauthorized_msg();
			flag=0;
		break;

				
	}
}


int main(void)
{	

	HAL_Servo_Init();
	
	HAL_LCD_Init();
	
	SPI_Config_t SPI_config;
	
	SPI_config.Mode					= SPI_MODE_SLAVE;
	SPI_config.CLK_Polarity			= SPI_CPOL_IDLE_LOW;
	SPI_config.CLK_Phase			= SPI_CPHA_1ST_EDGE;
	SPI_config.INT_Mode				= SPI_INT_ENABLE;
	SPI_config.First_Data_Transfer	= SPI_FDT_MSB;
	SPI_config.Polling_Mode			= SPI_POLLING_DISABLE;
	SPI_config.SS_Mode				= SPI_SS_MODE_SLAVE_INPUT;
	
	MCAL_SPI_Init(&SPI_config);
	sei();	
	
	lcd_default_msg();

	HAL_PIR_Init(&DDRA, PIR_PIN);
	
	while (1) 
    {
		if(servo==1 && (!HAL_PIR_GetState(&PINA, PIR_PIN)) )
		{
			HAL_Servo_Update(15);
			servo=0;
		}
    }
}




ISR(SPI_STC_vect)
{
	MCAL_SPI_Receive(&rData);
	servo=rData;
	GateAction(rData);
	_delay_ms(100);
	if(flag==0)
		flah_rled();
	else
		flah_gled();
	lcd_default_msg();
}