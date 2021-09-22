/*
 * EX5_search_for_elements.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	int arr[100], n, num;

	printf("Enter size of array: ");
	fflush(stdout);
	scanf("%d", &n);

	printf("Enter array elements\n");
	for(int i = 0 ; i < n ; i++)
	{
		printf("Enter number: ");
		fflush(stdout);
		scanf("%d", &arr[i]);
	}

	printf("Enter element to be searched: ");
	fflush(stdout);
	scanf("%d", &num);

	for (int i = 0 ; i < n ; i++)
	{
		if (num == arr[i])
		{
			printf("Number found at location %d", i+1);
			break;
		}

		if(i == n-1)
			printf("array does not include the number");
	}

	return 0;
}
