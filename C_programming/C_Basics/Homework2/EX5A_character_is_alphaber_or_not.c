/*
 * A_character_is_alphaber_or_not.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	char alpha;

	printf ("Enter a character: ");
	fflush(stdout);
	scanf ("%c", &alpha);

	if ((alpha >='a' && alpha <='z') || (alpha >='A' && alpha<='Z'))
		printf ("%c is an alphabet", alpha);
	else
		printf ("%c is not an alphabet", alpha);
}
