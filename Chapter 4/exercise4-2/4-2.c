#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
/* 
	Exercise 4-2: Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be e oe E and an optionally signed exponent. 
*/
double atof(char s[]);

int main()
{
    double x = 0;
    char num[] = "-123.7e+1";
    //int converted = atof(num);
    x = atof(num);
    printf("%f\n", x);
    return 0;
}

/* convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;
    double div = 1, mult = 1;

    for(i = 0; isspace(s[i]); i++) /* skip white spcae */
        ;

    sign = (s[i] == '-') ?  -1 : 1;
    if (s[i] == '+')
    {
        sign = 1;
        i++;
    }
    else if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    
    for (val = 0.0; isdigit(s[i]); i++) 
        val = 10 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10 * val + (s[i] - '0');
        power *= 10.0;
    }
    
    if (s[i] == 'e' || s[i] == 'E')
    {
        if (s[i+1] == '+')
        {
            for (i+=2; isdigit(s[i]); i++)
                mult *= 10;
            return (sign * mult) * (val / power);
        }
        else if (s[i+1] == '-')
        {
            for (i+=2; isdigit(s[i]); i++)
                div /= 10;
            return (sign * div) * (val / power);
        }

        printf("invalid input.\n");
        return -1;
    }
    
    
    return sign * val / power;
}