/*
 * EX7_Factorial.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */

#include <stdio.h>

int main()
{
	int num, original_num, fact=1;

	printf ("Enter an integer: ");
	fflush(stdout);
	scanf("%d", &num);
	original_num = num;

	if (num == 0)
		printf("Factorial = %d", 1);
	else if (num < 0)
		printf ("Error!!! Factorial of negative numbers does not exist");
	else
	{
		while(num > 0)
		{
			fact *= num;
			num--;
		}
		printf ("Factorial of %d is %d", original_num, fact);

	}



}
