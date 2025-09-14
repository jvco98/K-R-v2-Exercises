#include <stdio.h>

/* 
	Exercise 1-17: Write a program to print
	all input lines that are longer than
	80 characters.
*/

#define MAXLINE	1000	/* max input line size */
#define LIMIT		80		/* max input line size */

int _getline(char line[], int maxline);

int main()
{
	char line[MAXLINE], end;
	int lineLen;

	while((lineLen = _getline(line, MAXLINE)) > 0)
   {
   	if (lineLen > LIMIT)
   		printf("%s", line);
   }
   return 0;
}

/* getline: read a line into s, ret len */
int _getline(char s[], int limit)
{
	int c, i;

	for (i = 0; (i < limit) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}