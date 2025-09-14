/* 
   Exercise 1-13: Write a program to print a histogram of the lengths of words 
   in its input. It is easy to draw the histogram with the bars horitzontal; a 
   vertical orientation is more challenging.
*/

#include <stdio.h>

#define BLOCK  0333
#define MAXWL  20    // Max length of a word 
#define MAXNO  20    // Max # of words in a sentence 

int main()
{ 
   int c, wl, nc, wordIndex;   
   wordIndex = nc = wl = 0;
   int word[MAXNO] = {0};

   // rows = across
   // cols = vertical
   char histogram[MAXWL][MAXNO] = {0};

   while((c = getchar()) != EOF)
   {
      if (wl > MAXNO)   
      {
         printf("too many words.\n");
         return 1;
      }

      if (nc > MAXWL)
      {
         printf("word too long.\n");
         return 1;
      }

      if (c == ' ' || c == '\n' || c == '\t')
      {
         wl++;
         word[wordIndex] = nc;
         wordIndex++;
         nc = 0;
      }
      else
         nc++;
   }
   
   for (int i = MAXNO; i >= 0; i--)
   {
      printf("%3d | ", i);
      for (int j = 0; j <= MAXWL; j++)
      {
         if (i < word[j])
         {
            putchar(BLOCK);
         }
         else
            putchar(' ');

         printf(" ");
      }
      printf("\n");
   }

   for (int i = 0; i < MAXNO; ++i)
   {
      if (i == 0)  
         printf("%7c ", '_');
      else
         printf("_ ");
   }
   printf("\n");

   for (int i = 0; i < MAXNO; ++i)
   {
      if (i == 0)  
         printf("%7d ", word[i]);
      else
         printf("%d ", word[i]);
   }
   printf("\n");

}