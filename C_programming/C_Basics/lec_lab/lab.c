/*
 * lab.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */


#include <stdio.h>

int main()
{
	for (int i=0 ; i < 10 ; i++)
	{
		for (int j = i ; j < 10 ; j++)
		{
			printf("%d ", j);
		}
		printf("\n");
	}
}
