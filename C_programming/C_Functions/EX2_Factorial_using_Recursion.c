/*
 * EX2_Factorial_using_Recursion.c
 *
 *  Created on: Sep 28, 2021
 *      Author: mohamed

*/


#include <stdio.h>

int factorial(int n);

int main()
{
	int n ;
	printf("Enter a positive integer: ");
	fflush(stdout);
	scanf("%d", &n);
	printf("Factorial of %d is %d", n, factorial(n));

	return 0;
}


int factorial(int n)
{
	if (n != 1)
		return n * factorial(n-1);
	return 1;
}

