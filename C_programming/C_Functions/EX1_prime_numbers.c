/*
 * prime_numbers.c
 *
 *  Created on: Sep 28, 2021
 *      Author: mohamed
 */


#include <stdio.h>

void prime_numbers(int num1 , int num2);


int main()
{
	int num1, num2;

	printf("enter two numbers: ");
	fflush(stdout);
	scanf("%d%d", &num1, &num2);
	prime_numbers(num1 , num2);

	return 0;
}


void prime_numbers(int num1 , int num2)
{
	int i , j;
	printf("prime numbers between %d and %d are: ", num1 , num2);
	for (i = num1 ; i <= num2 ; i++)
	{
		for (j = i/2 ; j > 1 ; j--)
		{
			if (i % j == 0)
				break;

		}
		if(j == 1)
			printf("%d  ", i);
	}
}
