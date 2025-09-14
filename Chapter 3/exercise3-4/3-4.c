#include <stdio.h>
#include <stdint.h>
#include <limits.h>
/* 
	Exercise 3-4: In a two's complement number representation, our version of 'itoa' does not handle the largest negative number, that is, the value of n equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
*/

// The itoa function fails to handle the largest negative number in two's complement because of the line n = -n;.  In two's complement representation, the largest negative number, -(2^(wordsize-1)), when negated, results in a positive value that is outside the representable range of positive numbers for a signed integer of the same word size.  For example, in an 8-bit two's complement system, if n is -128 (the largest negative number), -n would ideally be +128. However, the range of 8-bit signed integers is -128 to +127.  Therefore, +128 cannot be represented as a positive 8-bit signed integer, leading to an overflow or undefined behavior.  The itoa function relies on converting the absolute value of the number to characters, and this conversion to a positive value fails for the largest negative number.

void itoa(int n, char s[]);

 ///itoa: convert n to characters in s
 void itoa(int n, char s[])
 {
     int i, sign;
     if(n == INT_MIN)
     	printf("largest negative # seen (%d)\n", INT_MIN);//-2^(sizeof(n)*8 -1));
     else if ((sign = n) < 0) // record sign 
         n = -n;         // make n positive 
     i = 0;
     do {                // generate digits in reverse order 
         s[i++] = n % 10 + '0';  // get next digit
     } while ((n /= 10) > 0);    // delete it
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     //reverse(s); //another function that reverses 's' string
 }


int main()
{
	int x;
	char s[1024];
	itoa(1<<31, s);
	return 0;
}