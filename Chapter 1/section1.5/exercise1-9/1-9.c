/* 
	Exercise 1-9: Write a program to copy its input to its output, replacing 
	each string of one or more blanks by a single blank.
*/
#include <stdio.h>
//#include <stdbool.h>

int main(void) 
{
	int blankcount, character;
	
	//bool blankLastSeen = false;
	
	while((character = getchar()) != EOF)
	{
			/*if(character == ' ')
			{
				if(blankLastSeen == false)
				{
					putchar(character);
					blankLastSeen = true;
				}
			}
			else
			{
				putchar(character);
				blankLastSeen = false;
			}*/
		
		
		blankcount = 0;
		while(character == ' ')
		{
			if(blankcount == 0)
			{
				putchar(character);
			}
			blankcount++;
			character = getchar();
		}
		putchar(character);
		
	}
	/* Why does EOF (Ctrl+Z) act funny? */
}