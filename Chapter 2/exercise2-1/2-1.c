#include <stdio.h>
#include <limits.h>
#include <float.h>
/* 
	Exercise 2-1: Write a program to determine the ranges of char, short, int and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point types.

*/

void prnt_std_datatypes();

int main()
{
	prnt_std_datatypes();

	/*
		Manually calculate data type values...
	*/
	
	
   return 0;
}


void prnt_std_datatypes()
{
	printf("\n\t\t~~ std header values ~~\n");
	printf("{CHAR_BIT} \t\t= {%d}\n", CHAR_BIT);
	printf("{SCHAR_MIN, SCHAR_MAX} \t= {%d, %d}\n", SCHAR_MIN, SCHAR_MAX);
	printf("{UCHAR_MAX} \t\t= {%d}\n", UCHAR_MAX);
	printf("{CHAR_MIN, CHAR_MAX} \t= {%d, %d}\n", CHAR_MIN, CHAR_MAX);
	printf("{SHRT_MIN, SHRT_MAX} \t= {%d, %d}\n", SHRT_MIN, SHRT_MAX);
	printf("{USHRT_MAX} \t\t= {%d}\n", USHRT_MAX);
	printf("{INT_MIN, INT_MAX} \t= {%i, %i}\n", INT_MIN, INT_MAX);
	printf("{UINT_MAX} \t\t= {%u}\n", UINT_MAX);
	printf("{LONG_MIN, LONG_MAX} \t= {%ld, %ld}\n", LONG_MIN, LONG_MAX);
	printf("{ULONG_MAX} \t\t= {%lu}\n", ULONG_MAX);
	printf("{LLONG_MIN, LLONG_MAX} \t= {%lli, %lli}\n", LLONG_MIN, LLONG_MAX);
	printf("{ULLONG_MAX} \t\t= {%llu}\n", ULLONG_MAX);
}