#include <stdio.h>
#include <limits.h>

/* 
	Exercise 3-6: Write a version of 'itoa' that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough. 
*/

 void itoa(int n, char s[], int b);

int main()
{
	char str[1024];
	itoa(INT_MIN, str, 7);
	printf("%s\n", str);
	return 0;
}

 ///itoa: convert n to characters in s
 void itoa(int n, char s[], int b)
 {
     int i, sign;
     /*if(n == INT_MIN)
     	printf("largest negative # seen (%d)\n", INT_MIN);
     else*/ if ((sign = n) < 0) // record sign 
         n = -n;         // make n positive 
     i = 0;
     do {                // generate digits in reverse order 
         s[i++] = n % 10 + '0';  // get next digit
     } while ((n /= 10) > 0);    // delete it
     if (sign < 0)
         s[i++] = '-';

     while(i < b)
     	s[i++] = ' ';

     s[i] = '\0';
     //reverse(s); //another function that reverses 's' string
 }