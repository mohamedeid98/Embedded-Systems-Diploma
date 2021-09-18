/*
 * EX8_Simple_Calculator.c
 *
 *  Created on: Sep 18, 2021
 *      Author: mohamed
 */


#include <stdio.h>

int main()
{
	char operator;
	float num1, num2;

	printf ("Enter an operator(+, -, *, /): ");
	fflush(stdout);
	scanf("%c", &operator);

	printf ("Enter two operands: ");
	fflush(stdout);
	scanf("%f%f", &num1, &num2);

	switch (operator)
	{
	case '+':
		printf ("%.2f + %.2f = %.2f", num1, num2, num1+num2);
		break;
	case '-':
		printf ("%.2f - %.2f = %.2f", num1, num2, num1-num2);
		break;
	case '*':
		printf ("%.2f * %.2f = %.2f", num1, num2, num1*num2);
		break;
	case '/':
		if (num2 == 0)
		{
			printf ("Error! Divide by zero");
			break;
		}
		printf ("%.2f / %.2f = %.2f", num1, num2, num1/num2);
		break;
	}

}
