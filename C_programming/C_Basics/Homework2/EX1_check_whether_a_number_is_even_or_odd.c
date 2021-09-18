/*
 * EX1_check_whether_a_number_is_even_or_odd.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	int num;


	printf("Enter a number: ");
	fflush(stdout);
	scanf("%d", &num);

	if (num %2 == 0)
		printf("%d is even\n", num);
	else
		printf("%d is odd\n", num);



	return 0;
}

