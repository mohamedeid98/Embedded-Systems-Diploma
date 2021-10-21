/*
 * EX3.c
 *
 *  Created on: Oct 21, 2021
 *      Author: mohamed
 */

#include <stdio.h>

struct Scomplex
{
	float real;
	float imaginary;
}x, y, z;

struct Scomplex add_complex(struct Scomplex z1 , struct Scomplex z2)
{
	struct Scomplex z;
	z.real = z1.real + z2.real;
	z.imaginary = z1.imaginary + z2.imaginary;
	return z;
}

int main()
{
	printf("for 1st complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f%f", &x.real, &x.imaginary);

	printf("for 2nd complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f%f", &y.real, &y.imaginary);

	z = add_complex(x, y);
	printf("sum = %0.1f+%0.1fi", z.real, z.imaginary);
	return 0;
}
