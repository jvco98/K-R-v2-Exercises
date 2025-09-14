#include <stdio.h>

/* 
	Exercise 1-22: Write a program to "fold" long input lines into two or more
	shorter lines after the last non-blank character that occurs before the n-th
	column of input. Make sure your program does something intelligent with very
	long lines, and if there are no blanks or tabs before the specified columns.
*/

#define MAXLINE 35

int main()
{
   int pos, c;
   // could work with two char arrays. arr1 holds raw entry.
   // arr 2 holds updated format (fold lines using '\n')
   // find out how to calculate current tab position
   // calculate each words length and compare them to the current tab position.
 	// if the current tab position + word length > MAXLINE, put a '\n' in the 
 	// starting position of the word (within arr2). The word in question follows
 	// the newly added '\n'. Repeat this process until EOF reached.
   for (pos = 0; (c = getchar()) != EOF; ++pos)
   {
   	if (pos < MAXLINE)
   		putchar(c);
   	else
   	{
   		if (c != ' ')
   			putchar(c);
   		else
   		{
   			pos = 0;
   			putchar('\n');
   		}
   	}	
   }

   return 0;
}