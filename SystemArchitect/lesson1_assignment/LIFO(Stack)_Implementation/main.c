/*
 * main.c
 *
 *  Created on: Nov 29, 2022
 *      Author: mohamed
 */
unsigned char buffer[5];

#include <stdio.h>
#include "LIFO.h"

int main(void)
{
	int i;
	LIFO lbuf;
	init(&lbuf, buffer, sizeof(buffer)/sizeof(buffer[0]));
	for(i = 0 ; i < 5 ; i++)
	{
		push(&lbuf, i);
	}
	for(i = 0 ; i < 5 ; i++)
	{
		unsigned char item ;
		pop(&lbuf, &item);
		printf("%X\n", item);
	}







	return 0;
}
