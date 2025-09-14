#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
/* 
	Exercise 3-5: Write the function 'itob(n,s,b)' that converts the integer 'n' into a base 'b' character representation in the string 's'. In particular, itob(n,s,16) formats n as a hexadecimal integers in 's'.
*/

void itob(int n, char s[], int b);
void reverse(int c, char s[]);

int main()
{
	char str[1024]; 
	int n, base;
	printf("enter a decimal number:\n");
	scanf("%d", &n);
	printf("enter a base number to be converted to:\n");
	scanf("%d", &base);
	printf("result:\n");
	itob(n, str, base);
	printf("%s\n", str);
	return 0;
}

void itob(int n, char s[], int b)
{
	int remainder, i = 0, count = 0;
	int final;

	while(n != 0)
	{
		remainder = n % b;
		//convert int to char
		remainder += '0';
		//printf("%d ", remainder);
		s[i++] = remainder;
		n /= b;
		count++;
	}
	s[i] = '\0';
	count -= 1;
	reverse(count, s);
}

void reverse(int c, char s[])
{
	char temp;

	for (int i = 0; i < c-i; i++)
	{
		temp = s[i];
		s[i] = s[c-i];
		s[c-i] = temp;
		//swap current with c - i until c == i
		//swap s[i] with s[c-i] until c == i 
	}
}
