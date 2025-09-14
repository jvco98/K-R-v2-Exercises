#include <stdio.h>

/* 
	Exercise 1-20: Write a program `detab` that replaces tab in the input with
	the proper number of blanks to spaces to the next tab stop. Assume a fixed
	set of tab stops, say every n columns. Should n be a variable or a symbolic
	paramter?
*/

#define TAB_STOPS 	8

int main()
{
	int i = 0;
	char c;
	while((c = getchar()) != EOF)
	{
		if (c == '\t')
			for (int blanks = TAB_STOPS - (i % TAB_STOPS); blanks > 0; blanks--)
			{
				putchar(' ');
				i++;
			}
		else if (c == '\n')
		{
			putchar('\n');
			i = 0;
		}
		else
		{
			putchar(c);
			i++;
		}
	}
	return 0;
}