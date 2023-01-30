#include <stdio.h>
#include <stdlib.h>

const char *PERSON_FORMAT = "%s %c \n";
const char *PERSON_FORMAT_READ = "%s %c %d %d %d\n";

typedef struct person
{
    char name[20];
    char gender; 
    int cid[3];   
}person;


int main()
{
    person p1 = {"mohamed", 'M'};
    person p2;
    person *p3;
    // FILE *file = fopen("data.dat", "w");
    // if(file == NULL)
    //      exit(1);
    // fprintf(file, PERSON_FORMAT, p1.name, p1.gender);
    // fclose(file);

    FILE *file = fopen("data.dat", "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
     
    // read file contents till end of file
    while(fscanf(file, PERSON_FORMAT_READ, &p2.name, &p2.gender, &p2.cid[0], &p2.cid[1], &p2.cid[2]) != EOF)
    {
        *p3 = p2;
        printf ("%s, %c, %d, %d, %d\n", p3->name, p3->gender, p3->cid[0], p3->cid[1], p3->cid[2]);
    }    
    // close file
    fclose (file);





    return 0;
}