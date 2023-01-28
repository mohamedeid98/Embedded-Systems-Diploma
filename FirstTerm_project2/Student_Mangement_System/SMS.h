/*
 * SMS.h
 *
 *  Created on: Jan 28, 2023
 *      Author: mohamed
 */

#ifndef SMS_H_
#define SMS_H_

typedef struct sinfo
{
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
	int cid[10];
	struct sinfo *next;
}student;

typedef struct database
{
	int size;
	student *head;
}data;

void add_student_file();
void add_student_manual();
void find_roll();
void find_fn();
void find_cid();
void get_total();
void delete();
void update();
void show();

#endif /* SMS_H_ */
