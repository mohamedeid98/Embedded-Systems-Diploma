/*
 * EX1.c
 *
 *  Created on: Oct 21, 2021
 *      Author: mohamed
 */

#include <stdio.h>

struct SStudent
{
	char name[10];
	int roll;
	float marks;
};


int main()
{
	struct SStudent student;

	printf("Enter information of the student\n");

	printf("Enter name: ");
	fflush(stdout);
	scanf("%s", student.name);

	printf("Enter roll number: ");
	fflush(stdout);
	scanf("%d", &student.roll);

	printf("Enter marks: ");
	fflush(stdout);
	scanf("%f", &student.marks);

	printf("\nDisplay Information\n");

	printf("name: %s\n", student.name);
	printf("roll: %d\n", student.roll);
	printf("marks: %0.2f\n", student.marks);



	return 0;
}
