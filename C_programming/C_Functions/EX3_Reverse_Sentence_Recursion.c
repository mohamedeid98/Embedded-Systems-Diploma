/*
 * EX3_Reverse_Sentense_Recursion.c
 *
 *  Created on: Sep 28, 2021
 *      Author: mohamed
 */


#include <stdio.h>
#include <string.h>

void reverse(char sentence[]);
static int i , j;
int main()
{
	char s[20] ;
	printf("Enter a sentence: ");
	fflush(stdout);
	gets(s);
	i = 0 ; j = strlen(s)-1;

	reverse(s);
	printf("%s", s);
	return 0;
}


void reverse(char sentence[])
{
	char temp;


	temp = sentence[i];
	sentence[i] = sentence[j];
	sentence[j] = temp;
	i++; j--;
	if (i != j)
		reverse(sentence);
}
