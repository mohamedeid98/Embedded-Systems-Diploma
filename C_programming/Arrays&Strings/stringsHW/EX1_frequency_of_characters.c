/*
 * EX1_frequency_of_characters.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	char str[100], c;
	int count=0;
	printf("Enter a string: ");
	fflush(stdout);
	gets(str);
	printf("Entered string: %s\r\n", str);

	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c", &c);

	for (int i=0 ; str[i] != '\0' ; i++)
	{
		if(c == str[i])
			count++;

	}
	printf("Frequency of %c is %d", c, count);

	return 0;
}
