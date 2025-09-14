#include <stdio.h>

/* 
	Exercise 1-13: Write a program to print a histogram of the lengths of words 
   in its input. It is easy to draw the histogram with the bars horitzontal; a 
   vertical orientation is more challenging.
*/

#define BLOCK  0333

int main()
{ 
   int c;   

   while((c = getchar()) != EOF)
   {
      if (c == ' ' || c == '\n' || c == '\t')
         putchar('\n');
      else
         putchar(BLOCK);
   }
}