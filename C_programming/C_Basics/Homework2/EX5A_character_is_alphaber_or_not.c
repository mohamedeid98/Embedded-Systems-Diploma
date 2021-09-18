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

	if ((alpha >=97 && alpha <=122) || (alpha >=65 && alpha<=90))
		printf ("%c is an alphabet", alpha);
	else
		printf ("%c is not an alphabet", alpha);
}
