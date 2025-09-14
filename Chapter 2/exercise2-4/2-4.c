#include <stdio.h>
#include <string.h>
/* 
	Exercise 2-4: Write an alternate version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2.

	squeeze: delete all c from s
	void squeeze(char s[], int c)
	{
		int i, j;

		for(int i = j = 0; s[i] != '\0'; i++)
			if(s[i] != c)
				s[j++] = s[i];
		s[j] = '\0';
	}
*/



int main()
{
	char phrase1[50], phrase2[50];
	printf("enter a short phrase:\n");
	gets(input1);
	printf("enter another short phrase:\n");
	gets(input2);
	printf("removing shared characters between phrases from first short phrase...\n");
	
	return 0;
}