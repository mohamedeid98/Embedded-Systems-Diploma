/*
 * EX1_sum_of_two_matrix.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	int i, j;
	float arr1[2][2], arr2[2][2], result[2][2];

	printf("Enter the elements of the 1st matrix!\n");
	for (i=0 ; i <2 ; i++)
	{
		for (j=0 ; j<2 ; j++)
		{
			printf("Enter a%d%d: \n", i+1, j+1);
			fflush(stdout);
			scanf("%f", &arr1[i][j]);
		}
	}


	printf("Enter the elements of the 2nd matrix!\n");
	for (i=0 ; i <2 ; i++)
	{
		for (j=0 ; j<2 ; j++)
		{
			printf("Enter a%d%d: \n", i+1, j+1);
			fflush(stdout);
			scanf("%f", &arr2[i][j]);
		}
	}

	printf("Matrix of Sum\n");
	for (i=0 ; i<2 ; i++)
	{
		for (j = 0 ; j < 2 ; j++)
		{
			result[i][j] = arr1[i][j] + arr2[i][j];
			printf("%0.1f   ", result[i][j]);
		}
		printf("\n");
	}

	return 0;
}
