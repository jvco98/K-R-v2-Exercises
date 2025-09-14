#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
/* 
	Exercise 2-6: Write a function setbits(x,p,n,y) that returns 'x' with the 
	'n' bits that begin at position p set to the rightmost n bits of 'y', 
	leaving the other bits unchanged.
*/

uint16_t setbits(uint16_t x, uint16_t p, uint16_t  n, uint16_t y);

int main()
{
	uint16_t x, y, pos, field_sz;

	for(;;)
	{
		printf("enter unsigned integer: ");
		int result1 = scanf("%hu", &x);
		printf("enter another unsigned integer: ");
		int result2 = scanf("%hu", &y);	

		if ((result1 && result2))
		{
			printf("enter a starting bit position\n");
			result1 = scanf("%hu", &pos);
			if (!((16 >= pos) && (pos >= 0)))
			{
				printf("invalid bit position received\n");
			}
			
			printf("how many bits do you need?\n");
			result2 = scanf("%hu", &field_sz);	
			if (field_sz > pos+1)
			{
				printf("you're asking for too many bits... must be smaller than starting bit position\n");
			}
						

			if ((result1 && result2))
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

	x = setbits(x, pos, field_sz, y);

	return 0;
}

/// setbits: set n bits from position p from y to x
uint16_t setbits(uint16_t x, uint16_t p, uint16_t n, uint16_t y)
{
	// grab n rightmost bits of y
	uint16_t y_mask = (y & ~(~0U << n)) << (p - n + 1);

	// create mask to clear n bits of x, starting at pos p
	uint16_t x_mask = ~((~0U << n) << (p - n + 1));

	// (make space in x for n bits at pos p) then append y bits to x
	x = (x & x_mask) | y_mask;

	return x;
}
