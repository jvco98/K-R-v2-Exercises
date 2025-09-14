#include <stdio.h>
#include "calc.h"
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f, int type)	{
	if (sp < MAXVAL){
		val[sp] = f;
		valType[sp] = type;	// push the type of value onto the stack
		sp++;
	}
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)	{
	if (sp > 0)
		return val[--sp];
	else 	{
		printf("error: stack empty\n");
	}
}