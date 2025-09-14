/* 
	Exercise 1-10: Write a program to copy its input to its output, replacing 
	each tab by \t, each backspace by \b, and each backlash by \\. This makes
	tabs and backspaces visible in an unambiguous way.
*/
#include <stdio.h>


int main(void) 
{
	int character;
	while((character = getchar()) != EOF)
	{
		if(character == '\n')
		{
			continue;
		}
		switch(character)
		{
			case '\t':
			{
				putchar('\\');
				putchar('t');
				break;
			}
			case '\b':
			{
				putchar('\\');
				putchar('b');
				break; 
			}
			case '\\':
			{
				putchar('\\'); 
				putchar('\\'); 
				break;
			}
			default:
				putchar(character);
				break;
		}
	}
}