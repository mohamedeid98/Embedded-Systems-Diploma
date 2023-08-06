/*
 * main.c
 *

 *      Author: Mohamed Eid
 */


#include "Utils.h"
#include "RegConfig.h"


void delay()
{
	for(volatile int i = 0 ; i < 10000 ; i++);
}

int main(void)
{
	unsigned char count = 0;
	ClearBit(DDRA, 0); // PORTA CONFIG

	DDRD = 0xFF;


	while(1)
	{
		if(ReadBit(PINA, 0) == 1)
		{
			while(ReadBit(PINA, 0) == 1);
			if (count >= 0 && count <= 7)
			{
				SetBit(PORTD, count);
				delay();
				count++;
			}
			else
			{
				count = 0;
				PORTD = 0x00;
				delay();
			}
		}
	}



}









