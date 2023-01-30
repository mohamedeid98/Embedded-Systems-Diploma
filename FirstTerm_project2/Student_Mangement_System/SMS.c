/*
 * SMS.c
 *
 *      @Author: Mohamed Eid
 */

#include "SMS.h"

const char *STUDENT_FORMAT = "%s %s %d %f %d %d %d %d %d\n";


void add_student_file(data *pdata, char *filename)
{
	student *phead;
	student temp;
	student *new_student;

	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
	while(fscanf(file, STUDENT_FORMAT, &temp.fname, &temp.lname, &temp.roll, &temp.GPA, &temp.cid[0], &temp.cid[1], &temp.cid[2], &temp.cid[3], &temp.cid[4]) != EOF)
	{
		phead = pdata->head;
		while(phead && pdata->size != 0)
		{
			if(phead->roll == temp.roll)
				break;
			phead = phead->next;
		}

		if(phead)
		{
			printf("Error! roll number already taken\n");
			//free(new_student);
		}
		else
		{
			new_student = (student*)malloc(sizeof(student));
			*new_student = temp;
			if(pdata->head == NULL)
			{
				pdata->head = new_student;
				pdata->tail = new_student;
			}
			else
			{
				pdata->tail->next = new_student;
				pdata->tail = new_student;
			}
			new_student->next = NULL;
			pdata->size++;

		}

		//printf("%s %s\n", new_student->fname, new_student->lname);

	}

	fclose (file);


}




void show(data *pdata)
{
	int i = 1;
	student *phead;
	phead = pdata->head;
	while(phead)
	{
		printf("Student %d details are...\n", i++);
		printf("First name is: %s\n", phead->fname);
		printf("Last name is: %s\n", phead->lname);
		printf("GPA is: %f\n", phead->GPA);
		printf("Enrolled Courses are: \n");
		for(int i = 0 ; i < 5 ; i++)
		{
			printf("course %d ID is: %d\n", i+1, phead->cid[i]);
		}
		printf("\n");
		phead = phead->next;
	}
}



void get_total(data *pdata)
{
	printf("Total number of students is: %d", pdata->size);
}


void update(data *pdata)
{
	int roll, choice, flag=0;
	student *phead = pdata->head;
	printf("Enter a roll number to update its data: ");
	fflush(stdout);
	scanf("%d", &roll);

	while(phead)
	{
		if(phead->roll == roll)
		{
			flag=1;
			printf("1. first name.\n");
			printf("2. last name.\n");
			printf("3. gpa.\n");
			printf("4. courses.\n\n");
			printf("Enter your choice: ");
			fflush(stdout);
			scanf("%d", &choice);
			switch(choice)
			{
			case 1:
				printf("Enter first name: ");
				fflush(stdout);
				scanf("%s", phead->fname);
				break;
			case 2:
				printf("Enter last name: ");
				fflush(stdout);
				scanf("%s", phead->lname);
				break;
			case 3:
				printf("Enter GPA: ");
				fflush(stdout);
				scanf("%f", &phead->GPA);
				break;
			case 4:
				printf("Enter courses IDs");
				fflush(stdout);
				for(int i ; i < 5 ; i++)
				{
					scanf("%d", &phead->cid[i]);
				}
				break;
			default:
				printf("wrong choice\n");
				break;
			}
		}
		phead = phead->next;
		if(flag)
			break;
	}
	if(!flag)
		printf("roll number is not found\n");
}


void delete(data *pdata)
{
	int roll, flag=0;
	student *curr, *prev;
	prev = pdata->head;
	curr = pdata->head->next;
	printf("Enter a roll number: ");
	fflush(stdout);
	scanf("%d", &roll);

	if(pdata->head->roll == roll)
	{
		pdata->head = pdata->head->next;
		pdata->size--;
		flag=1;
		free(prev);
	}
	else
	{
		while(curr)
		{
			if(curr->roll == roll)
			{
				prev->next = curr->next;
				free(curr);
				pdata->size--;
				flag=1;
				break;
			}
			prev = prev->next;
			curr = curr->next;
		}

	}
	if(!flag)
	{
		printf("roll is not found\n");
		return;
	}
}


void find_roll(data *pdata)
{
	int roll;
	student *phead;
	phead = pdata->head;
	printf("Enter roll number: ");
	fflush(stdout);
	scanf("%d", &roll);
	while(phead)
	{
		if(phead->roll == roll)
			break;
		phead = phead->next;
	}
	if(!phead)
	{
		printf("roll number is not found\n");
	}
	else
	{
		printf("Student details are...\n");
		printf("First name is: %s\n", phead->fname);
		printf("Last name is: %s\n", phead->lname);
		printf("GPA is: %f\n", phead->GPA);
		printf("Enrolled Courses are: \n");
		for(int i = 0 ; i < 5 ; i++)
		{
			printf("course %d ID is: %d\n", i+1, phead->cid[i]);
		}
	}
}

void find_cid(data *pdata)
{
	int flag, id;
	student *phead;
	phead = pdata->head;
	printf("Enter a course ID: ");
	fflush(stdout);
	scanf("%d", &id);
	flag=0;
	while(phead)
	{
		for(int i = 0 ; i < 5 ; i ++)
		{
			if(phead->cid[i] == id)
			{
				printf("\nStudent details are...\n");
				printf("First name is: %s\n", phead->fname);
				printf("Last name is: %s\n", phead->lname);
				printf("GPA is: %f\n", phead->GPA);
				flag++;
				break;
			}

		}
		phead = phead->next;
	}
	if(!flag)
		printf("Course ID not found");
}


void find_fn(data *pdata)
{
	int flag;
	char name[50];
	student *phead;
	phead = pdata->head;
	printf("Enter a name: ");
	fflush(stdout);
	scanf("%s", name);
	flag=0;
	while(phead)
	{
		if(!strcmp(name, phead->fname))
		{
			printf("\nStudent details are...\n");
			printf("First name is: %s\n", phead->fname);
			printf("Last name is: %s\n", phead->lname);
			printf("GPA is: %f\n", phead->GPA);
			printf("Enrolled Courses are: \n");
			for(int i = 0 ; i < 5 ; i++)
			{
				printf("course %d ID is: %d\n", i+1, phead->cid[i]);
			}
			flag++;
		}
		phead = phead->next;
	}
	if(flag == 0)
		printf("Name is not found\n");
}





void add_student_manual(data *pdata)
{
	int i, roll;
	student *phead;

	student *new_student = (student*)malloc(sizeof(student));


	printf("Student first name: ");
	fflush(stdout);
	scanf("%s", new_student->fname);
	printf("Student last name: ");
	fflush(stdout);
	scanf("%s", new_student->lname);
	printf("Student roll number: ");
	fflush(stdout);

	scanf("%d", &roll);
	phead = pdata->head;
	while(phead && pdata->size != 0)
	{
		if(phead->roll == roll)
			break;
		phead = phead->next;
	}

	if(phead)
	{
		printf("Error! roll number already taken\n");
		free(new_student);
	}
	else
	{
		new_student->roll = roll;
		printf("Student GPA: ");
		fflush(stdout);
		scanf("%f", &new_student->GPA);
		printf("Course IDs: ");
		fflush(stdout);

		i = 0;
		while(i < 5)
		{
			scanf("%d", &new_student->cid[i]);
			i++;
		}

		if(pdata->head == NULL)
		{
			pdata->head = new_student;
			pdata->tail = new_student;
		}
		else
		{
			pdata->tail->next = new_student;
			pdata->tail = new_student;
		}
		new_student->next = NULL;
		pdata->size++;

	}

}
