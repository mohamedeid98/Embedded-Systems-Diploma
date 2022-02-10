/*
 * handle_pointers.c
 *
 *  Created on: Feb 10, 2022
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{

	int m;
	m = 29;
	printf("Address of m : 0x%x \nValue of m : %d", &m , m);
	printf("\n\n");
	int *ab = &m;
	printf("Address of m : 0x%x \nValue of m : %d", ab , *ab);
	printf("\n\n");
	m = 34;
	printf("Address of m : 0x%x \nValue of m : %d", ab , *ab);
	printf("\n\n");

	*ab = 7;
	printf("Address of m : 0x%x \nValue of m : %d", &m , m);
	return 0;
}

