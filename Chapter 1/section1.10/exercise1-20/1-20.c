#include <stdio.h>

/* 
	Exercise 1-20: Write a program `detab` that replaces tab in the input with
	the proper number of blanks to spaces to the next tab stop. Assume a fixed
	set of tab stops, say every n columns. Should n be a variable or a symbolic
	paramter?
*/

#define TAB_STOPS 	8

void getline(char input[]);

int main()
{
	char asd[50] = {'\0'};
   getline(asd);
   printf("%s", asd);
   return 0;
}

void getline(char input[])
{
	int blanks, i = 0;
	char c;
	while((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			// 
			//while( TAB_STOPS - (i % TAB_STOPS))
			while((i % TAB_STOPS) != 0 || i == 0)
			{
				if (i == 0)
				{
					while (i < TAB_STOPS)
					{
						input[i] = ' ';
						i++;
					}
				}
				else
				{
					input[i] = ' ';
					i++;
				}
			}
		}
		else {
			input[i] = c;
			i++;
		}

	}
}