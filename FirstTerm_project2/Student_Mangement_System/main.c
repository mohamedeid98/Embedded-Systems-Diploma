/*
 * main.c
 *
 *  Created on: Jan 28, 2023
 *      Author: mohamed
 */


#include "SMS.h"

int main()
{
	data pdata;
	pdata.head = NULL;
	pdata.tail = NULL;
	pdata.size = 0;
	add_student_manual(&pdata);
	add_student_manual(&pdata);
	show(&pdata);
	//update(&pdata);
	//find_roll(&pdata);
	printf("\n%d\n", pdata.size);

	//add_student_manual(&pdata);
	//printf("\n%d\n", pdata.size);
	//find_fn(&pdata);
	//find_cid(&pdata);
	//get_total(&pdata);


	return 0;
}
