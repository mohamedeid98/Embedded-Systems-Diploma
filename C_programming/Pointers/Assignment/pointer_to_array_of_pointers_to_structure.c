#include <stdio.h>

struct employee
{
	char *name;
	int id;
};


int main()
{
	struct employee emp1={"Jhon", 1001}, emp2={"Alex", 1002}, emp3={"Taylor", 1003};
	struct employee *arr[] = {&emp1, &emp2, &emp3};

	struct employee **ptr = arr;

	printf("Employee Name : %s\n", (**(ptr+1)).name);
	printf("Employee ID : %d",(**(ptr+1)).id);







	return 0;
}
