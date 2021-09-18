/*
 * EX4.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	float num1, num2;

	printf ("Enter two numbers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f", &num1, &num2);
	printf ("Product: %f", num1*num2);
}
