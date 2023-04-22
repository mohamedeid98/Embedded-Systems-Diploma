/*
 * Assignment.c
 *
 *  Author: Mohamed Eid
 */ 

#include "Utils.h"
#include "RegConfig.h"


void delay()
{
	for(volatile int i = 0 ; i < 10000 ; i++);
}

int main(void)
{
	//unsigned char counter;
	//PORTA CONFIG
	//ClearBit(DDRA, 0);
	//SetBit(PORTA, 0) ;
	
	// PORTD CONFIG
	DDRD = 0xFF;
	
	unsigned char i ;
    while(1)
    {
		for (i = 0 ; i <= (unsigned char)7 ; i++)
		{
			SetBit(PORTD, i);
			delay();
		}
		
		for (i = 0 ; i <= (unsigned char)7 ; i++)
		{
			ClearBit(PORTD, (7-i));
			delay();
		}
				
		
		//PORTD = 0x00;
		//delay();
		

    }
}
