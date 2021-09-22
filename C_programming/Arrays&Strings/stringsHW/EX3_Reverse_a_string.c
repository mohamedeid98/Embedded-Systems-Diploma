/*
 * EX3_Reverse_a_string.c
 *
 *  Created on: Sep 22, 2021
 *      Author: mohamed
 */


#include <stdio.h>
#include <string.h>

int main()
{
	int i, j;
	char str[100], temp;

	printf("Enter a string: ");
	fflush(stdout);
	gets(str);

	for(i=0, j=strlen(str)-1 ; i < j ; i++, j--)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
	}

	printf("%s", str);

	return 0;
}
