#include <stdio.h>

/* 
	Exercise 1-6: Verify that the expression getchar() != EOF is 0 or 1 
*/

int main()
{
	int c;
	//printf("%d", getchar() != EOF);
	
	while( c = getchar() != EOF)
	{
		printf("%d\n", c);
	}
	printf("%d\n", c);
	return 0;
}