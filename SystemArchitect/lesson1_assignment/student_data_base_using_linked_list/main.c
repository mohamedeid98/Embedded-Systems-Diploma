/*

 main.c
 	@Author Mohamed Eid

 */
#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
	int ID;
	char name[40];
	float height;
	struct student *Pnext_student;
}Student;

Student *Data_Base = NULL;


void AddStudent();
int DeleteStudent(int key);
void ViewStudents();
void Fill_Record(Student *New_Student);
int DeleteAll();
Student *Get_Nth_Node();
void print_student(Student *student);
int Data_Base_length();
Student *Nth_Node_from_End();
Student *Middle_Student();
void reverse();
void options();


int main()
{

	int choice, key;

	options();
	printf("\n Enter a number: ");
	fflush(stdout);
	scanf("%d", &choice);
	while(choice)
	{
		switch(choice)
		{
		case 1:
			AddStudent(Data_Base);
			break;
		case 2:
			printf("Enter key: ");
			fflush(stdout);
			scanf("%d", &key);
			if(DeleteStudent(key));
			else
				printf("key not found");

			break;
		case 3:
			ViewStudents(Data_Base);
			break;
		case 4:
			if(DeleteAll())
				printf("Database deleted\n");
			else
				printf("already empty\n");
			break;
		case 5:;
			Student *student;
			student = Get_Nth_Node();
			if(student)
				print_student(student);
			else
				printf("index not found\n");
			break;
		case 6:
			printf("\nDatabase length is: %d\n", Data_Base_length());
			break;
		case 7:;
			Student *NthStudent = Nth_Node_from_End();
			if(NthStudent)
				print_student(NthStudent);
			break;
		case 8:;
			Student *Mid_Student = Middle_Student();
			if(Mid_Student)
				print_student(Mid_Student);
			else
				printf("Empty Database\n");
			break;
		case 9:
			reverse();
			break;
		default:
			printf("wrong choice");
			break;
		}
		options();
		printf("\n Enter a number: ");
		fflush(stdout);
		scanf("%d", &choice);
	}




	return 0;
}


void AddStudent()
{
	Student *NewStudent;
	Student *temp = Data_Base;

	if(Data_Base == NULL)
	{
		NewStudent = (Student*)malloc(sizeof(Student));
		Data_Base = NewStudent;
	}
	else
	{
		while(temp->Pnext_student)
		{
			temp = temp->Pnext_student;
		}
		NewStudent = (Student*)malloc(sizeof(Student));
		temp->Pnext_student = NewStudent;
	}


	Fill_Record(NewStudent);

	NewStudent->Pnext_student = NULL;

}



int DeleteStudent(int key)
{
	Student *prev_student = NULL;
	Student *target_student = Data_Base;


	if(Data_Base)
	{
		while(target_student)
		{
			if(target_student->ID == key)
			{
				if(prev_student)
				{
					prev_student->Pnext_student = target_student->Pnext_student;
				}
				else
				{
					Data_Base = target_student->Pnext_student;
				}
				free(target_student);
				return 1;
			}
			prev_student = target_student;
			target_student = target_student->Pnext_student;
		}
	}
	return 0;
}

void ViewStudents()
{
	int i = 1;
	Student *temp = Data_Base;
	if(Data_Base == NULL)
		printf("Empty Data_Base\n");
	while(temp)
	{
		printf("Record Number %d\n", i);
		print_student(temp);
		temp = temp->Pnext_student;
		i++;
	}
}

void print_student(Student *student)
{

	fflush(stdin); fflush(stdout);
	printf("ID: %d\n", student->ID);
	fflush(stdin);fflush(stdout);
	printf("Name: %s\n", student->name);
	fflush(stdin);fflush(stdout);
	printf("Height: %f\n\n", student->height);
}

void Fill_Record(Student *New_Student)
{
	printf("Enter the ID: ");
	fflush(stdout);
	scanf("%d", &New_Student->ID);
	printf("Enter Student Full Name: ");
	fflush(stdout);
	scanf("%s", New_Student->name);
	printf("Enter Height: ");
	fflush(stdout);
	scanf("%f", &New_Student->height);
}
int DeleteAll()
{
	Student *curr_student = Data_Base;
	if(Data_Base)
	{
		while(curr_student)
		{
			Student *temp = curr_student;
			curr_student = curr_student->Pnext_student;
			free(temp);

		}
		Data_Base = NULL;
		return 1;
	}
	return 0;
}

Student *Get_Nth_Node()
{
	int idx;
	printf("\n enter index: ");
	fflush(stdout);
	scanf("%d", &idx);
	int i = 0;
	Student *temp = Data_Base;
	while(temp)
	{
		if(i == idx)
		{
			return temp;
		}
		temp = temp->Pnext_student;
		i++;
	}
	return NULL;
}

int Data_Base_length()
{
	Student *temp = Data_Base;
	int i = 1;
	if(Data_Base)
	{
	while(temp->Pnext_student)
	{
		temp = temp->Pnext_student;
		i++;
	}
	return i;
	}
	return 0;
}

Student *Nth_Node_from_End()
{
	Student *p_ref = Data_Base;
	Student *p_main = Data_Base;

	int n, i=0;
	printf("enter the Nth node: ");
	fflush(stdout);
	scanf("%d", &n);

	for(i = 0 ; i < n ; i++)
	{
		p_ref = p_ref->Pnext_student;
	}
	while(p_ref)
	{
		p_ref = p_ref->Pnext_student;
		p_main = p_main->Pnext_student;
	}
	return p_main;
}

Student *Middle_Student()
{
	Student *p_fast, *p_slow;
	p_fast = Data_Base;
	p_slow = Data_Base;
	if(Data_Base->Pnext_student)
	{
		while(p_fast->Pnext_student)
		{
			p_fast = p_fast->Pnext_student->Pnext_student;
			p_slow = p_slow->Pnext_student;
		}
	}
	return p_slow;
}
void reverse()
{
	Student *prev = NULL, *next = NULL, *curr = Data_Base;
	while(curr)
	{
		next = curr->Pnext_student;
		curr->Pnext_student = prev;
		prev = curr;
		curr = next;
	}
	Data_Base = prev;
}
void options()
{
	printf ("\n=========================") ;
			printf ("\n \t choose one of the following options \n") ;
			printf ("\n 1:Add Student") ;
			printf ("\n 2:Delete Student") ;
			printf ("\n 3:View All Students") ;
			printf ("\n 4:Delete All Students") ;
			printf ("\n 5:Get Nth Student from Beginning") ;
			printf ("\n 6:Get Number of Students in DataBase") ;
			printf ("\n 7:Get Nth Student from End") ;
			printf ("\n 8:Get the middle of students");
			printf ("\n 9:Reverse Students") ;

			printf ("\n=========================") ;
}

