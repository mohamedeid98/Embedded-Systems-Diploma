/*
 * main.c
 *
 *  Created on: Jan 28, 2023
 *      Author: mohamed
 */


#include "SMS.h"

int main()
{
	char filename[20] = "data.dat";
	data pdata;
	pdata.head = NULL;
	pdata.tail = NULL;
	pdata.size = 0;

	int choice;
	printf ("\n-------------------------------------------\n") ;
	printf ("1  : Add New Student Manually \n") ;
	printf ("2  : Add New Student from File \n") ;
	printf ("3  : Find Student With ID \n") ;
	printf ("4  : Find Student With First Name \n") ;
	printf ("5  : Find Students Registered in a course \n") ;
	printf ("6  : Find Students Count \n") ;
	printf ("7  : Delete a Student \n") ;
	printf ("8  : Update a Student \n") ;
	printf ("9  : View All Students \n") ;

	fflush(stdout);
	scanf("%d", &choice);


	while(choice)
	{
		switch(choice)
		{
		case 1:
			add_student_manual(&pdata);
			break;
		case 2:
			add_student_file(&pdata, filename);
			break;
		case 3:
			find_roll(&pdata);
			break;
		case 4:
			find_fn(&pdata);
			break;
		case 5:
			find_cid(&pdata);
			break;
		case 6:
			get_total(&pdata);
			break;
		case 7:
			delete(&pdata);
			break;
		case 8:
			update(&pdata);
			break;
		case 9:
			show(&pdata);
			break;
		default:
			printf("wrong choice!\n");
			break;
		}

		printf ("\n-------------------------------------------\n") ;
		printf ("1  : Add New Student Manually \n") ;
		printf ("2  : Add New Student from File \n") ;
		printf ("3  : Find Student With ID \n") ;
		printf ("4  : Find Student With First Name \n") ;
		printf ("5  : Find Students Registered in a course \n") ;
		printf ("6  : Find Students Count \n") ;
		printf ("7  : Delete a Student \n") ;
		printf ("8  : Update a Student \n") ;
		printf ("9  : View All Students \n") ;

		fflush(stdout);
		scanf("%d", &choice);
	}




	/*add_student_file(&pdata, "data.dat");
	//add_student_manual(&pdata);
	//add_student_manual(&pdata);
	show(&pdata);
	//update(&pdata);
	//find_roll(&pdata);
	printf("\n%d\n", pdata.size);

	//add_student_manual(&pdata);
	//printf("\n%d\n", pdata.size);
	//find_fn(&pdata);
	//find_cid(&pdata);
	//get_total(&pdata);*/


	return 0;
}
