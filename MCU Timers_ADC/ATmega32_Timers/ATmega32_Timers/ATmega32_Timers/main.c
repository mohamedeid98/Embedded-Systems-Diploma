/*
 * ATmega32_Timers.c
 *
 * Created: 8/22/2023 2:30:01 AM
 * Author : Mohamed
 */ 

#include "MCAL/TIMER/timer.h"

void callback_fun()
{
	PORTA = ~PORTA;
}

int main(void)
{
	
	DDRA = 0xFF;
	sei();
	TIMER0_CONFIG_t CONFIG = {MODE_CTC, CLK_PRESCALER_8, OCInterrupt_ENABLE, TOInterrupt_DISABLE, NULL, callback_fun};
	TIMER0_Init(&CONFIG);
	TIMER0_SetCompVal(0xF0);
     while (1) 
    {
    }
}

