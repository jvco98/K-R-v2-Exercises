#include <stdio.h>

/* 
	Exercise 1-21: Write a program `entab` that replaces strings of blanks by the
	minumum number of tabs and blanks to achieve the same spacing. Use the same
	tab stops as for detab(exercise1-20). When either a tab or a single blank would
	suffice to reach a tab stop, which should be given preference?
*/

#define TAB_STOPS 	8

int main()
{
   int tabs, blanks, pos, c;
   blanks = tabs = 0;

   for (pos= 1; (c = getchar()) != EOF; ++pos)
   {
   	if (c == ' ')	{
   		if ((pos % TAB_STOPS) != 0)
   			blanks++;
   		else {
   			blanks = 0;
   			tabs++;
   		}
   	}	else	{
   		for (; tabs > 0; --tabs)
   			putchar('\t');
   
   		if (c == '\t')
   			blanks = 0;
   		else 
   			for (; blanks > 0; --blanks)
   				putchar('.');
   		
   		putchar(c);

   		if (c == '\n')
   			pos = 0;
   		else if (c == '\t')
   			pos += TAB_STOPS - (pos % TAB_STOPS);
   	}
   }

   return 0;
}
