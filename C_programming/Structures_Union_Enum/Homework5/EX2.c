/*
 * EX2.c
 *
 *  Created on: Oct 21, 2021
 *      Author: mohamed
 */

#include <stdio.h>

struct SDistance
{
	int feet;
	float inch;
}d1, d2, result;


int main()
{
	printf("Enter information for 1st distance\n");
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%d", &d1.feet);
	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f", &d1.inch);

	printf("\nEnter information for 2nd distance\n");
	printf("Enter feet: ");
	fflush(stdout);
	scanf("%d", &d2.feet);
	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f", &d2.inch);

	result.feet = d1.feet + d2.feet;
	result.inch = d1.inch + d2.inch;

	while(result.inch > 12.0)
	{
		result.inch -= 12;
		++result.feet;
	}
    printf("\nSum of distances = %d\'-%.1f\"", result.feet, result.inch);

	return 0;
}
