/*
 * EX3_The_largest_of_3.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */


#include <stdio.h>

int main()
{
	float num1, num2, num3;

	printf ("Enter three numbers: ");
	fflush(stdout);
	scanf("%f%f%f", &num1, &num2, &num3);

	if (num1 > num2)
	{
		if (num1 > num3)
			printf("Largest number = %.2f", num1);
		else
			printf("Largest number = %.2f", num3);
	}
	else if (num2 > num1)
	{
		if (num2 > num3)
			printf ("Largest number = %.2f", num2);
		else
			printf ("Largest number = %.2f", num3);
	}
}
