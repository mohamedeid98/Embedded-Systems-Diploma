/*
 * EX4_Insert_Elements.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	int arr[100], n, loc, i, num;

	printf("Enter array size:");
	fflush(stdout);
	scanf("%d", &n);

	printf("Enter array elements\r\n");
	for (i = 0 ; i < n ; i++)
	{
		printf("Enter number: ");
		fflush(stdout);
		scanf("%d", &arr[i]);
	}

	printf("Enter the element to be inserted: ");
	fflush(stdout);
	scanf("%d", &num);

	printf("Enter the location: ");
	fflush(stdout);
	scanf("%d", &loc);

	for (i = n ; i >= loc  ; i--)
	{
		arr[i] = arr[i-1];
	}
	arr[loc-1] = num;

	printf("New array\r\n");
	for (i = 0 ; i < n+1 ; i++)
	{
		printf("%d  ", arr[i]);
	}

	return 0;
}
