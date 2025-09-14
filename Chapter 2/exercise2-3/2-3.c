#include <stdio.h>
#include <string.h>
/* 
	Exercise 2-3: Write the function htoi(s), which converts a string of
	hexadecimal digits (including an optional 0x or 0X) into its equivalent
	integer value. The allowable digits are 0 through 9, a through f, and A through F.
*/

unsigned long long power(int base, int n);
unsigned long long htoi(char digits[], int digitz_sz);

int main()
{
	int result, input_sz;
	char input[64];
	printf("enter a hexadecimal digit:\n");
	gets(input);
	printf("equivalent integer value: %lld\n", htoi(input, strlen(input)-1));
	return 0;
}

/// convert string of hex digits to int value
unsigned long long htoi(char digit[], int digit_sz)
{
	unsigned long long result = 0;
	int exponent = 0;

	for (int i = digit_sz; i >= 0; i--)
	{
		if ((digit[i] >= '0') && (digit[i] <= '9'))
			result += (digit[i] - '0') * (power(16, exponent));
		else if (digit[i] >= 'a' && digit[i] <= 'f')
			result += (digit[i] -'a' + 10) * (power(16, exponent));
		else if (digit[i] >= 'A' && digit[i] <= 'F')
			result += (digit[i] -'A' + 10) * (power(16, exponent));

		++exponent;
	}
	return result;
}

/// power: raise base to n'th power; n >= 0
unsigned long long power(int base, int n)
{
	unsigned long long p;
	p = 1;

	for (int i = 0; i < n; ++i)
		p *= base;
	return p;
}