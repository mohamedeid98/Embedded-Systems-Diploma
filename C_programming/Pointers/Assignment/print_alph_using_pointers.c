/*
 * print_alph_using_pointers.c
 *
 *  Created on: Feb 10, 2022
 *      Author: mohamed
 */


#include<stdio.h>



int main()
{
	char alpha[26];
	int i;

	for(i = 0 ; i < 26 ; i++)
	{
		*(alpha+i) = 'A' + i;
	}

	for(i = 0 ; i < 26 ; i++)
	{
		printf("%c ", *(alpha+i));
	}






	return 0;
}
