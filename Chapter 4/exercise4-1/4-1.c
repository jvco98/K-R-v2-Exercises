#include <stdio.h>
#include <limits.h>
#include <string.h>
/* 
	Exercise 4-1: Write the function strrindex(s, t), which returns the position of the rightmost occurrence of 't' in 's', or -1 if there is none.
*/

int strrindex(char s[], char t[]);


int main()
{
    printf("%d", strrindex("I stopped dreaming a long long time ago.", "ago"));
	return 0;
}

/// return index of 't' in 's', -1 if nonew
int strrindex(char s[], char t[])
{
	int found = 0, status = 0, index;
    for (int i = strlen(s); i > 0; i--)
    {
    	if (s[i] == t[0]) //sniffed something?
    	{
    		if (i+strlen(t) > strlen(s)) // false alarm?
    			continue;

    		printf("%c ", t[0]);
    		
    		index = i+1;	// smells like truffles 
    		for (int j = 1; t[j] != '\0'; j++)
    		{
    			int local = i;
    			if (s[index++] == t[j])
    				printf("%c ",t[j]);
    			if (t[j+1] == '\0')
    				return local;
    		}
    	}
    }
    return -1;
}