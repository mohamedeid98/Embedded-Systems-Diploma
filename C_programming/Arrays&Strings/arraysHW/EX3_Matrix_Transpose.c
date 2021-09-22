/*
 * EX3_Matrix_Transpose.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	float arr[10][10];
	int i, j, row, col;

	printf("Enter size of the matrix: ");
	fflush(stdout);
	scanf("%d%d", &row, &col);

	printf("Enter elements of the matrix\n");
	for (i = 0 ; i < row ; i++)
	{
		for (j = 0 ; j < col ; j++)
		{
			printf("Enter number: ");
			fflush(stdout);
			scanf("%f", &arr[i][j]);
		}
	}

	printf("Entered matrix\r\n");
	for (i = 0 ; i < row ; i++)
	{
		for (j = 0 ; j < col ; j++)
		{
			printf("%0.2f   ", arr[i][j]);
		}
		printf("\n");
	}


	printf("Matrix Transpose\r\n");
	for (i = 0 ; i < col ; i++)
	{
		for (j = 0 ; j < row ; j++)
		{
			printf("%0.2f   ", arr[j][i]);
		}
		printf("\n");
	}

	return 0;
}
