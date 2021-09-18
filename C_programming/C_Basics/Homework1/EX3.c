/*
 * EX3.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */


#include <stdio.h>

int main()
{
	int num1, num2;
	printf ("Enter two intgers: ");
	fflush(stdin); fflush(stdout);
	scanf ("%d%d", &num1, &num2);
	printf ("Sum: %d", num1+num2);
}
