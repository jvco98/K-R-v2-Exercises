/* 
	Exercise 1-12: Write a program that prints its input one word per line.
*/
#include <stdio.h>

int main(void) 
{
	int c;

	while((c = getchar()) != EOF)
	{
		// determine state
		if (c == ' ' || c == '\n' || c == '\t')
		{
			putchar('\n');
		}
		else 
		{
			putchar(c);
		}
	}

}