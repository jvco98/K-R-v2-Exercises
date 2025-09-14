#include <stio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[])	{
	int i, c, sign = 0;

	/* skip whitespace */
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	
	/* look for variable, operator, mathop */
	if (!isdigit(c) && c != '.')
	{
		
		if (c == '\n' || c == ' ' || c == '\t')	/* found whitespace */
			return c;
		else if (ispunct(c))	/* found non alphanumeric character (cmd or operator) */
		{
			if (c <= '/' && c >= '%' || c == '=') // found operator
			{
				return OPERATOR;
			}
			if (c <= '$' && c >= '!') // found operator
			{
				return CMD;
			}

			printf("\nerror: unknown command: %c\n",c);
			return -1;
		}
		else {	
			// check for variable
			char temp = getch();
			if ((temp == ' ') || (temp == '\n') || (temp == '\t'))	// found variable
				return VARIABLE;
			else 
			{
				char str[5];
				int k=0;
				str[k++] = c;
				str[k++] = temp;

				// get next 2 char, check for mathop
				while(isalpha((str[k++] = getchar()))) {;}
				str[k] = '\0';

				if (strcmp(str, "cos\n") == 0)
					return MATHOP;
				else if (strcmp(str, "sin\n") == 0)
					return MATHOP;
				else if (strcmp(str, "exp\n") == 0)
					return MATHOP;
				else if (strcmp(str, "pow\n") == 0)
					return MATHOP;
				else
				{
					printf("unknown command: %s", str);
					return '\n';
				}
			}
		}
	}
	
	/* get number */
	i = 0;
	if (c == '-') 	{
		s[i] = c;
		if (!isdigit(c = getch()))	{
			return '-';
		}
		else
			s[++i] = c;
	}
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));

	s[i] = '\0';
	//printf("%s\n", s);
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}