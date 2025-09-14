#include <stdio.h>

/* 
   Exercise 1-14: Write a program to print a histogram of the 
   frequencies of different characters in its input.
*/

#define BLOCK  0333
#define rows   10
#define cols   10

int main()
{ 
   /*
      create 2d array with first (bottom) row (x) being word lengths [x, y] = [~25, ~y]
      and first column (y) being number of times word of x length is seen
      get length of current word and store in variable
      iterate through 2d array, incrementing num_times_seen variable (column)
      print 2d array
   */

   int c, nchars = 0;

   // rows = across
   // cols = vertical
   char histogram[rows][cols] = {0};

   int wordlength[cols] = {0};  
   // wordlenth[0] = 1, wordlength[1] = 2, ... , wordlength[n] = n+1;

   // grab frequency of words 
   // to populate wordlentth[]
   while((c = getchar()) != EOF)
   {
      if (c == ' ' || c == '\n' || c == '\t')
      {
         for (int i = 0; i < cols; ++i)
         {
            if (nchars == (i+1))  
            {
               wordlength[i]++;
            }
         }
         //printf("word length: %d\n", nchars);
         nchars = 0;
      }
      else
         nchars++;
   }

   // populate histogram matrix
   for (int i = cols-1; i >= 0; i--)
   {
      for (int j = 0; j < cols; j++)
      {
         if (wordlength[j] > 0)
         {  
            histogram[i][j] = BLOCK;
            wordlength[j]--;
         }/*
         else
            putchar('~');
         putchar(' ');

         if (j == cols-1)
            printf("\n");*/
      }
   }

   // print histogram matrix to screen
   for (int i = 0; i < rows; ++i)
   {
      for (int j = 0; j < cols; ++j)
         printf("%c ", histogram[i][j]);

      printf("\n");
   }
}