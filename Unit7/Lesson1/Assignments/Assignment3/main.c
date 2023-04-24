/*
 * main.c
 *
 *      @Author: Mohamed Eid
 *
 */

#include <util/delay.h>
#include "Utils.h"
#include "RegConfig.h"

//#define F_CPU 8000000UL


//static unsigned char SevenSegmentNumber[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
//static unsigned char SegmentNumber[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int main(void)
{
	int i, j ;

	DDRC = 0x7F;

	while(1)
	{
		for (i = 0 ; i <= 9 ; i++)
		{
			for(j = 0 ; i <= 9 ; j++)
			{
				PORTC = 0b1011 | (i << 4);
				_delay_ms(50);
				PORTC = 0b0111 | (j << 4);
				_delay_ms(50);
			}
			_delay_ms(500);
		}
	}
}



