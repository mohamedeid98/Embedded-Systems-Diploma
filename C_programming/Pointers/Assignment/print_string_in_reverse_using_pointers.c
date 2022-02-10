#include <stdio.h>
#include <string.h>

int main()
{
	int i=0;
	char s[20];
	char *ptr = s;
	printf("Input a string: ");
	fflush(stdout);
	scanf("%s", s);

	while(*ptr)
	{
		ptr++;
		i++;
	}
	//printf("string base address = 0x%x\nlast character address = 0x%x\nnumber of characters = %d",s,ptr,i);
	while(i)
	{
		ptr--;
		printf("%c",*ptr);
		i--;
	}








/*	int i;
	char s[20];

	printf("Input a string: ");
	fflush(stdout);
	scanf("%s", s);
	char *ptr = s + strlen(s)-1;
	for(i = 0 ; i < strlen(s) ; i++)
	{
		printf("%c", *ptr);
		ptr--;
	}*/




	return 0;
}
