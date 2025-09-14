#include <stdio.h>

int main()
{
   float fahr, celsius;
   int lower, upper, step;
   
   lower = 0;	/* lower limit of temperature table */
   upper = 300; /* upper limit */
   step = 20;	/* step size */
 
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFahrenheit to Celsius conversion\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   for (fahr = upper; fahr >= lower; fahr -= step) {
      printf("%3.0f %6.1f\n", fahr, (5.0/9.0)*(fahr - 32.0));   
   }
}