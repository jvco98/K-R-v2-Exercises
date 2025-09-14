#include <stdio.h>
#include <stdbool.h>
/* 
	Exercise 2-2: Write a loop equivalent to 

		for (int i = 0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
			s[i] = c;
	
	without using && or ||
*/

int main()
{
	int lim = 10;
	char c, s[9];

	for (int i = 0; (i < lim-1); ++i)
	{
		c = getchar();
		if (c == '\n')
			break;
		if (c == EOF)
			break;
		s[i] = c;
	}
	return 0;
}

