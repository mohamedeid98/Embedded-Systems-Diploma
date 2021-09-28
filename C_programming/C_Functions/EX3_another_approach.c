/*
 * EX2_another_approach.c
 *
 *  Created on: Sep 28, 2021
 *      Author: mohamed
 */


#include <stdio.h>

void reverse(void);

int main()
{
	printf("Enter a sentence: ");
	reverse();

	return 0;
}


void reverse(void)
{
	char c;
	fflush(stdout);
	scanf("%c", &c);

	if (c != '\n')
	{
		reverse();
		printf("%c", c);
	}
}
