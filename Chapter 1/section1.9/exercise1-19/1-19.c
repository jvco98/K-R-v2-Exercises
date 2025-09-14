#include <stdio.h>

/* 
	Exercise 1-19: Write a function reverse(s) that reverses the character string
	s. Use it to write a program that reverses its input a line at a time.
*/

#define MAXLINE	50		/* max input line size */

int _getline(char line[], int lim);
void reverse_arr(char arr[], int len);

int main()
{
	char line[MAXLINE];
	int len;
	
	while ((len = _getline(line, MAXLINE)) > 0)
		reverse_arr(line, len);
	
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


void reverse_arr(char arr[], int len)
{
	int downcount = len - 2; /* ignore line's '\n' and '\0' char */

	for (int upcount = 0; upcount < downcount; upcount++)
	{
		char temp = arr[upcount];
		arr[upcount] = arr[downcount];
		arr[downcount] = temp; 
		downcount--;
	}
	printf("%s\n", arr);
}