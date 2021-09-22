/*
 * EX3_length_of_string.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */


#include <stdio.h>

int main()
{
	int i;
	char str[100];
	printf("Enter a string: ");
	fflush(stdout);
	gets(str);

	for (i = 0 ; str[i] != '\0' ; i++);

	printf("length of string = %d", i);

	return 0;
}
