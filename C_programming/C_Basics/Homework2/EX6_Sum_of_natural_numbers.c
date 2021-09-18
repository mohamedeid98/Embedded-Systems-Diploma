/*
 * EX6_Sum_of_natural_numbers.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	int n, sum=0;

	printf ("Enter an intger: ");
	fflush(stdout);
	scanf("%d", &n);

	for (int i=1; i <= n ; i++)
		sum += i;

	printf ("Sum = %d", sum);

	return 0;
}


