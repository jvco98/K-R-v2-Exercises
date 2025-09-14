#include <stdio.h>

/* 
	Exercise 1-18: Write a program to remove
	trailing blanks and tabs from each line
	of input, and to delete entirely blank
	lines.
*/

#define MAXLINE	50		/* max input line size */

int _getline(char line[], int lim);

int main()
{
	char line[MAXLINE];
	int len;
	
	while ((len = _getline(line, MAXLINE)) > 0)
		if (remove_trail(line) > 0)
			printf("%s", line);
	
  	return 0;
}

/* getline: read a line into s */
int _getline(char s[], int lim)
{
	int c, i;

	for (i = 0; ((i < lim - 1) && (c = getchar()) != EOF) && (c != '\n'); ++i)
		s[i] = c;

	if ((c == '\n') && (i != 0)) {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

/* removetrail: removes trailing blanks and tabs. */
/* Go to End and proceed backwards removing */
int remove_trail(char rline[])
{	
	int i;

	/* consider rline[] without '\n' */
	for (i = 0; rline[i] != '\n'; i++);
	/* compensate for 0-index */
	i--;
	
	/* if ' ' or '\t' seen, decrease index */
	for (i > 0; ((rline[i] == ' ') || (rline[i] == '\t')); i--);

	if (i >= 0)
	{
		i++;
		rline[i] = '\n';
		i++;
		rline[i] = '\0';
	}

	return i;
}