/*
 * check_Vowel_or_Consonant.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	char alpha;

	printf ("Enter an alphabet: ");
	fflush(stdout);
	scanf("%c", &alpha);

	if (alpha == 'a' || alpha == 'A' ||  alpha == 'e' || alpha == 'E' || alpha == 'i' || alpha == 'I' || alpha == 'o' || alpha == 'O' || alpha == 'u' || alpha == 'U')
		printf ("%c is a vowel", alpha);
	else
		printf ("%c is a consonant", alpha);
}
