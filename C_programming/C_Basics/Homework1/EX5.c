/*
 * EX5.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	char character;
	printf ("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf ("%c", &character);
	printf ("ASCII of %c is %d", character, character);
}
