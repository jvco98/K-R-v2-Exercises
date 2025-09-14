#include <stdio.h>

/* 
	Exercise 1-22: Write a program to "fold" long input lines into two or more
	shorter lines after the last non-blank character that occurs before the n-th
	column of input. Make sure your program does something intelligent with very
	long lines, and if there are no blanks or tabs before the specified columns.
*/

#define MAXLINE			35	/* Largest acceptable line length */
#define TAB_SZ				8
#define CURR_TAB_SZ(X)	(TAB_SZ - (X % TAB_SZ))	/* Amount of blank spaces until the next tab index */

int getline(char raw[], int lim);
int WORD_END_POS(char raw[], int pos);

int main()
{
   char raw[MAXLINE], folded[100];
   int rawsize, pos;
   rawsize = pos = 0;


   while((rawsize = getline(raw, MAXLINE)) > 0)
   {
   	printf("~rawsize: %d~\n", rawsize);
   	for (pos = 0; raw[pos] != '\n'; ++pos)
   	{
   		if (WORD_END_POS(raw, pos) > MAXLINE)
   			printf("overflow\n");
   		printf("1st check: %d\n", WORD_END_POS(raw, pos));

   		if ( (pos + CURR_TAB_SZ(pos)) > MAXLINE)
   			printf("overflow\n");
   		printf("2nd check: %d\n", pos + CURR_TAB_SZ(pos));
   	}
   }
   //printf("~%d~\n", rawsize);	


   return 0;
}


int getline(char raw[], int lim) 
{
	int c, i;
	for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
		raw[i] = c;
	if ((c == '\n') && (i != 0))
	{
		raw[i] = c;
		i++;
	}

	raw[i] = '\0';

	return i;
}

int WORD_END_POS(char raw[], int pos)
{
	for (int i = pos; raw[i] != ' '; ++i)
	return i;
}