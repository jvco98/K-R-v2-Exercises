#include <stdio.h>
#include <stdbool.h>

/* 
	Exercise 1-23: Write a program to remove all comments from a C program. Don't
	forget to handle quoted strings and character constants pproperly. C-comments
	do not nest.
*/

int main()
{
	char c; int i;
	bool inComment, inMultiComment; 
	inComment = inMultiComment = false;

	while((c = getchar()) != EOF)
	{
		if (c == '/')
		{	
			char temp = c;
			c = getchar();
			if (c == '/')
			{
				inComment = true;
				c = getchar();
			}
			else if (c == '*')
			{	
				char x = NULL; 
				while (x != '*') 
					x = getchar();
				if ((c = getchar()) == '/')
				{
					c = getchar();
					inMultiComment = false;
					if (c != ' ')
						putchar(c);
					else
						c = getchar();
				}
			}
			else
			{
				putchar(temp);
				inComment = inMultiComment = false;
			}				
		}
		
		if (inComment || inMultiComment)
		{
			if (inComment && (c == '\n'))
				inComment = false;
		}
		else
			putchar(c);
	}
   return 0;
}