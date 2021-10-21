/*
 * EX4.c
 *
 *  Created on: Oct 21, 2021
 *      Author: mohamed
 */

#include <stdio.h>

struct SStudent
{
	int roll;
	char name[10];
	float marks;
}student[10];

int main()
{
	int i =0;
	printf("Enter information of students\r\n");
	do
	{
		student[i].roll = i+1;
		printf("For roll number: %d\n", student[i].roll);
		printf("Enter name: ");
		fflush(stdout);
		scanf("%s", student[i].name);
		printf("Enter marks: ");
		fflush(stdout);
		scanf("%f", &student[i].marks);
		i++;
	}
	while(i < 10);

	printf("\nDisplay\r\n");
	for(i = 0 ; i < 10 ; i++)
	{
		printf("Name: %s  ", student[i].name);
		printf("Marks: %0.1f", student[i].marks);
		printf("\n");

	}

	return 0;
}

