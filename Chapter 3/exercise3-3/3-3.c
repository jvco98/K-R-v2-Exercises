#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
/* 
	Exercise 3-3: Write a function 'expand(s1, s2)' that expands shorthand notation like a-z in the string s1 into the equivalentt complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
*/

void expand(char s1[], char s2[]);
int isAlpha(char c);

#define ISLOWER 3
#define ISUPPER 2
#define ISDIGIT 1

int main()
{
	char s1[1024], s2[1024], c;
	int i = 0, j = 0;

    while ((c = getchar()) != EOF)
		s1[i++] = c;
	s1[i] = '\0';

	/*int firstchar = s1[0];
	printf("first char:%d\n", firstchar);
	int lastchar = s1[strlen(s1) - 1];
	printf("last char:%d\n", lastchar);
	*/
	//printf("you entered: %s\n", s1);
	expand(s1, s2);
	printf("%s\n", s2);
	return 0;
}

/// @brief expands shorthand notation (a-z becomes a b c d ... x y z) from string s1 into string s2
/// @param s1 String to be copied from 
/// @param s2 String to be copied to
void expand(char s1[], char s2[])
{
	// determine starting char
	// determine ending char

	int i = 0, j = 0;	
	int start = 0, end = 0;
	//bool isDigit = false, isUpper = false, isLower = false;

	while(s1[i] != '\0')
	{
		if (i == 0 && s1[i] == '-')
			s2[i++] = s1[i];
		else if (s1[i] == '-')
		{
			start = s1[i-1];
			end = s1[i+1];

			if (((s1[i] == '-' && i == 0)) || s1[i] == '\0')
				s2[j++] = '-';
			else if ((s1[i-2] == '-') || (s1[i+2] == '-'))
				printf("leading or trailing '-' found\n");
			if(isupper(start) && (isupper(end)) || (islower(start) && (islower(end))) || (isdigit(start) && (isdigit(end))))
			{
				//printf("start -- int: %d, char: %c\nend -- int: %d, char: %c\n", start, start, end, end);
				for (int x = start; x < end + 1; x++)
					s2[j++] = x;	
				s2[j] = '\0';
				i++;	
			}
			else
				printf("ranges are not of same type...\n");
		}
		i++;
	}
}

int isAlpha(char c)
{
	int x = c;
	if ((x >= 48) && (x <= 57))
		return 1;
	if ((x >= 65) && (x <= 90))
		return 2;
	else if ((x >= 97) && (x <= 122))
		return 3;
	else
		return -1;
}