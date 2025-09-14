#include <stdio.h>

/* 
	Exercise 1-15: Rewrite the temperature 
	conversion program of Section 1.2 to use
	a function for conversion.
*/

#define LOWER	0		/* lower limit of temperature table */
#define UPPER	300 	/* upper limit */
#define STEP	20		/* step size */

void fahrToCelsius(float fahr, float celsius);

int main()
{
   float fahr, celsius;
   fahrToCelsius(fahr, celsius);
   return 0;
}


void fahrToCelsius(float fahr, float celsius) {
	fahr = LOWER;
   
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFahrenheit to Celsius conversion\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   while (fahr <= UPPER) {
   	celsius = (5.0/9.0) * (fahr-32.0);
   	printf("%3.0f %6.1f\n", fahr, celsius);
   	fahr = fahr + STEP;
   }
}