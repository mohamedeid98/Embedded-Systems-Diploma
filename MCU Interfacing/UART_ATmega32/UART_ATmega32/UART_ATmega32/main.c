/*
 * UART_ATmega32.c
 *
 * Created: 8/6/2023 5:56:10 AM
 * Author : Mohamed Eid
 */ 

#include "MCAL/UART/uart.h"
#include "HAL/LCD/lcd.h"

int main(void) {

	char Txstr[] = "UART ATmega32";
	char RxStr[20];
	char cha;
	int x=0;

	LCD_INIT();
	UART_Init();
	UART_SendString(Txstr);
    /* Replace with your application code */
	sei();
	RX_INTERRUPT_EN();

    while (1) {
		
		/* Using periodic check
		LCD_Send_Command(LCD_BEGIN_AT_SECOND_RAW);
		if(UART_ReceivePeriodic(&cha))
		{
			LCD_Display_Character(cha);
			
		} */
		
		
		LCD_Send_Command(LCD_BEGIN_AT_FIRST_RAW);
		_delay_ms(20);
		LCD_Intger_Number(x++);
		if(x == 10)
			x = 0 ;
		_delay_ms(1000);
		
		/* Send and Receive using polling 
		UART_ReceiveString(RxStr);
		LCD_Send_Command(LCD_BEGIN_AT_SECOND_RAW);
		LCD_display_String(RxStr);
		LCD_display_String("              "); */
		
	}
}

ISR(USART_RXC_vect)
{
	LCD_Send_Command(LCD_BEGIN_AT_SECOND_RAW);
	LCD_Display_Character(UDR);
}