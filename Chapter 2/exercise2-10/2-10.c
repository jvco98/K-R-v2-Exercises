#include <stdio.h>
#include <stdint.h>

/* 
	Exercise 2-10: Rewrite the function 'lower', which converts upper case letters to lower
	case, with a conditional expression instead of if-else.
*/

///Convert upper case ASCII to lower case ASCII
void lower(char c);

int main()
{
	char letter;	
	printf("enter an upper-case letter: ");
	scanf("%c", &letter);
	//printf("SHHH!... try ~~~%c~~~ instead.\n", lower(letter));
	lower(letter);
}


///Convert upper case ASCII to lower case ASCII
void lower(char c)
{
	(c >= 'A' && c <= 'Z') ? printf("SHHH!... try ((( %c ))) instead.\n", c+32)	 : printf("could not find an upper-case letter\n");
}