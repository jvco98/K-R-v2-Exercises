#include <stdio.h>

/* 
	Exercise 1-x: Count the number of occurences of each digit, white space characters
	(blank, tab, newline), and of all other characters.
*/

int main()
{
   int c, i, nwhite, nother;
   int ndigit[10] = {0};

   nwhite = nother = 0;

   while((c = getchar()) != EOF)
   {
   	/* [[[  '0' <= c <= '9'  ]]] uses the  < and  >  operators, which
   		have a left rto right association. This would evaluate '0' <= c 
   		and result in a 0 or 1. Then, the program evaluate (0 or 1) <= '9',
   		which will always be true... Not exactly what we want... So we must
   		break this statement up and explicitly state we want to know
   		if ('0' <= c) && (c <= '9')
		*/
   	if(('0' <= c) && (c <= '9'))
   		ndigit[c-'0']++;
   	else if( c == ' ' || c == '\n' || c == '\t')
   		nwhite++;
   	else
   		nother++;
   }

   // print ndigits array to console
   for (int i = 0; i < 10; ++i) 
   {
   	if (i == 0)
   	{
   		printf("white spaces: %d\n", nwhite);
   		printf("other characters: %d\n", nother);
   		printf("ndigits[] = [ %d, ", ndigit[i]);
   	}
   	else if (i == 9)
   	{
   		printf("%d ]", ndigit[i]);
   		break;
   	}
   	else
   		printf("%d, ", ndigit[i]);
   }

   return 0;
}