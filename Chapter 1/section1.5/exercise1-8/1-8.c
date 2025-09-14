#include <stdio.h>

/* 
	Exercise 1-8: Write a program to count blanks, tabs, and newlines.
*/
int main(void) 
{
	int blanks, tabs, nl, character;
	blanks = tabs = nl = 0;
	while((character = getchar()) != EOF)
	{
		switch(character)
		{
			case '\n':
			{
				++nl;
				break;
			}
			case '\t':
			{
				++tabs;
				break;
			}
			case ' ':
			{
				++blanks;
				break;
			}
		}
	}
	printf("blanks: %d, tabs: %d, newlines: %d\n", blanks, tabs, nl);
}