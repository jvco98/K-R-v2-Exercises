#include <stdio.h>
#include <stdint.h>

int binsearch(int x, int v[], int n);
/* 
	Exercise 3-1: Our binary search makes two tests inside the loop, when one would suffice
	(at the price of more tests outside). Write a version with only one test inside the loop 
	and measure the difference in run-time.
*/

/*
	binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
	int binsearch(int x, int v[], int n)
	{
		int low, high, mid;

		low = 0;
		high = n-1; 
		while(low <= high)
		{
			mid = (low  + high) / 2;
			if(x < v[mid])
				high = mid - 1;
			else if (x > v[mid])
				low = mid + 1;
			else			// found match
				return mid;
		}
		return -1;			// no match found
	}
*/
int main()
{
	int n = 7;
	int arr[7] = {1,2,3,4,5,6,7};
	int x = binsearch(5, arr, n);
	printf("binsearch: %d\n", x);
	return 0;
}
///binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n-1; 
	
	while(low <= high)
	{
		mid = (low  + high) / 2;
		if ( x > v[mid] )
			low = mid + 1;
		else
			high = mid - 1;
	}

	if(x == v[mid])
		return mid;
	else			// found match
		return -1;
}