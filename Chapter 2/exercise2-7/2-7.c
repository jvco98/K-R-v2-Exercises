#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* 
	Exercise 2-7: Write a function invert(x,p,n) that returns x with the n bits that begin at 
	position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/

uint16_t invert(uint16_t x, uint16_t p, uint16_t n);

int main()
{
	uint16_t x, pos, n;
 
	for(;;)
	{
		printf("enter unsigned integer: ");
		int result = scanf("%hu", &x);

		if (result)
		{
			printf("enter a starting bit position\n");
			result = scanf("%hu", &pos);
			if (!((16 >= pos) && (pos >= 0)))
			{
				printf("invalid bit position received\n");
			}
			
			printf("how many bits do you need?\n");
			int result2 = scanf("%hu", &n);	
			if (pos + n > 16)
			{
				printf("you're asking for too many bits... must be smaller than starting bit position\n");
			}
						

			if (result)
				break;
			else
			{
				printf("invalid input\n");
				return 1;		
			}
		}	
		else
		{
			printf("invalid input\n");
			return 1;
		}
	}

	x = invert(x, pos, n);
	printf("result: %d\n", x);
	return 0;
}

/// invert: inverts n bits of x, starting at position p
uint16_t invert(uint16_t x, uint16_t p, uint16_t n)
{
	// create mask for bits of interest
	uint16_t mask = (~(~0U << n)) << (p - n + 1);
	// invert n bits at pos p
	return x ^ mask;
}
