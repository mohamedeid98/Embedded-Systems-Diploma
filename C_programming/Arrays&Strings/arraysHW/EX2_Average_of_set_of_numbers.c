/*
 * EX2_Average_of_set_of_numbers.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	float arr[100], sum=0 ;
	int i, n;

	printf("Enter number of data: ");
	fflush(stdout);
	scanf("%d", &n);

	for (i = 0 ; i < n ; i++)
	{
		printf("Enter number: ");
		fflush(stdout);
		scanf("%f", &arr[i]);
	}

	for (i = 0 ; i < n ; i++)
	{
		sum += arr[i];
	}
	printf("Average = %0.2f", sum/n);

	return 0;
}
