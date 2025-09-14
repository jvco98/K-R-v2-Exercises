#include <stdio.h>
#include <stdint.h>

/* 
	~~~~~~~~ 2's complement = flip bits then add 1 ~~~~~~~~~~~~~~~~~~~~~~~
	Exercise 2-9: In a 2's complement number system, x &= (x-1) deletes the rightmost 1-bit
	in x. Explain why. Use this observation to write a faster version of bitcount.

	bitcount: count 1-bits in x
	int bitcount(unsigned x)
	{
		int b;

		for(b = 0; x |= 0; x >>= 1)
			if (x & 01)
				b++;
		return b;
	}
*/
int bitcount(unsigned x);

int main()
{
	/* 
		The operation x &= (x - 1) effectively deletes the rightmost 1-bit in x because 
		subtracting 1 flips the bits starting from the rightmost 1-bit in x, and the bitwise 
		AND with x clears this bit.
    */
    int x;
	printf("Enter a binary number:\n");
	scanf("%d",&x);
	printf("Number of 1-bits in number: %d\n", bitcount(x));
}

int bitcount(unsigned x)
{
	int i;
	while(x != 0)
	{
		x &= (x-1);
		i++;
	}
	return i;
}