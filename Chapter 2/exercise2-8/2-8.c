#include <stdio.h>
#include <stdint.h>

/* 
	Exercise 2-8: Write a function rightrot(x,n) that returns the value of the integer x 
	rotated to the right by n bit positions.
*/

uint16_t rightrot(uint16_t x, uint16_t n);

int main()
{
	uint16_t x, n;
 
	for(;;)
	{
		printf("enter unsigned integer: ");
		int result = scanf("%hu", &x);

		if (result)
		{
			printf("shift right by how many bit positions?\n");
			result = scanf("%hu", &n);
			if (!((16 >= n) && (n >= 0)))
			{
				printf("invalid bit position received\n");
			}
			else
				break;
		}	
		else
		{
			printf("invalid input\n");
			return 1;
		}
	}

	x = rightrot(x, n);
	printf("result: %d\n", x);
	return 0;
}

/// rightrot: rotate x to the right by n bit positions
uint16_t rightrot(uint16_t x, uint16_t n)
{
	// get size of data to be manipulated
	int data_sz_bits = sizeof(x)*8;

	// store n bits that will be lost to shift
	uint16_t rotated_bits = (x & (~(~0U << n))) << (data_sz_bits - n); 

	// do stuff
	return ((x >> n) | rotated_bits);
}
