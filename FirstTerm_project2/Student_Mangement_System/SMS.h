/*
 * SMS.h
 *
 *  Created on: Jan 28, 2023
 *      Author: mohamed
 */

#ifndef SMS_H_
#define SMS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sinfo
{
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
	int cid[5];
	struct sinfo *next;
}student;

typedef struct database
{
	int size;
	student *head;
	student *tail;
}data;

void add_student_file();
void add_student_manual(data *);
void find_roll(data *);
void find_fn(data *);
void find_cid(data *);
void get_total(data *);
void delete(data *);
void update(data *);
void show(data *);

#endif /* SMS_H_ */
