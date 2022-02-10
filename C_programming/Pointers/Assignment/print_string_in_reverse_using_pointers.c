#include <stdio.h>
#include <string.h>

int main()
{
	int i;
	char s[20];

	printf("Input a string: ");
	fflush(stdout);
	scanf("%s", s);
	char *ptr = s + strlen(s)-1;
	for(i = 0 ; i < strlen(s) ; i++)
	{
		printf("%c", *ptr);
		ptr--;
	}




	return 0;
}
