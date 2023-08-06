/*
 * keypad.c
 *
 * Created: 6/25/2023 9:30:48 AM
 *  Author: Mohamed Eid
 */ 
#include "keypad.h"
#include<avr/io.h>
#include<util/delay.h>

int keypad_row[] = {R0, R1, R2 ,R3};
int keypad_col[] = {C0, C1, C2 ,C3};
	
void keypad_init()
{
	KEYPAD_DDR &= ~ (1 << R0) | (1 << R1) | (1 << R2) | (1 << R3);
	KEYPAD_DDR |= (1 << C0) | (1 << C1) | (1 << C2) | (1 << C3);
	KEYPAD_PORT = 0xFF;
}



char keypad_getkey()
{
	int i, j;
	for(i = 0 ; i < 4 ; i++)
	{
		KEYPAD_PORT |= ((1 << keypad_col[0]) | (1 << keypad_col[1]) | (1 << keypad_col[2]) | (1 << keypad_col[3])) ;
		KEYPAD_PORT &= ~(1 << keypad_col[i]);
		
		for(j = 0 ; j < 4 ; j++)
		{
			if(!(KEYPAD_PIN & (1 << keypad_row[j])))
			{
				while(!(KEYPAD_PIN & (1 << keypad_row[j])));
				switch(i)
				{
					case 0:
						switch(j)
						{
							case 0:
								return '7';
								break;
							case 1:
								return '4';
								break;
							case 2:
								return '1';
								break;
							case 3:
								return '?';
								break;
						}
						break;
					case 1:
						switch(j)
						{
							case 0:
							return '8';
							break;
							case 1:
							return '5';
							break;
							case 2:
							return '2';
							break;
							case 3:
							return '0';
							break;
						}
						break;
					
					case 2:
						switch(j)
						{
							case 0:
							return '9';
							break;
							case 1:
							return '6';
							break;
							case 2:
							return '3';
							break;
							case 3:
							return '=';
							break;
						}
						break;
					
					case 3:
						switch(j)
						{
							case 0:
							return '/';
							break;
							case 1:
							return '*';
							break;
							case 2:
							return '-';
							break;
							case 3:
							return '+';
							break;
						}
						break;
						
				}
			}
		}
	}
	return 'A';	
}
