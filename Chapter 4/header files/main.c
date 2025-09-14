#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#define MAXOP 100

int main()	{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF)	{
		switch (type)	{
			case NUMBER:
				push(atof(s), NUMBER);
				break;
			case VARIABLE:
				switch (s[0])	{
					case 'a' ... 'z':
						push(s[0]-'a', VARIABLE);	// push the variable index onto the stack
						break;
					default:
						break;
				}
				break;
			case OPERATOR:
				if (sp <= 2)
				{	
					//determine whether operators are variables or numbers
					bool op2_isvar = (valType[sp - 1] == VARIABLE);
					bool op2_isnum = (valType[sp - 1] == NUMBER);
    				bool op1_isvar = (valType[sp - 2] == VARIABLE);
    				bool op1_isnum = (valType[sp - 2] == NUMBER);

					// grab the two top values from the stack
					double op2 = pop(); double op1 = pop(); 

					switch (s[0])	{
						case '=':
							if (op2_isvar)
							{
								if (op1_isnum)
									vars[(int)op2] = op1;	// assign the value to the variable
								if(op1_isvar)
									vars[(int)op2] = vars[(int)op1];
	
								push(vars[(int)op2], NUMBER);	// push the variable index back onto the stack
							}
							else
								printf("error: invalid assignment\n");
							break;
						case '+':
							push(resolveOperand(op2, op2_isvar) + resolveOperand(op1, op1_isvar) , NUMBER);
							break;
						case '*':
							push(resolveOperand(op2, op2_isvar) * resolveOperand(op1, op1_isvar) , NUMBER);
							break;
						case '-':
							push(resolveOperand(op2, op2_isvar) - resolveOperand(op1, op1_isvar) , NUMBER);
							break;
						case '/':
							if (resolveOperand(op2, op2_isvar) != 0.0)
								push(resolveOperand(op1, op1_isvar) / resolveOperand(op2, op2_isvar), CMD);
							else
								printf("error: zero divisor\n");
							break;
						case '%':
							 if (resolveOperand(op2, op2_isvar) != 0.0)
								push(fmod(resolveOperand(op1, op1_isvar), resolveOperand(op2, op2_isvar)), NUMBER);
							else
								printf("error: zero divisor\n");
							break;
						default:
							break;
					}
				}
				else
					printf("error: expected at least 2 operators\n");
				break;
			case CMD:
				switch (s[0])	{
					case '$':
						showTop();
						break;
					case '#':
						duplicate(OPERATOR);
						break;
					case '"':
						swapItems(OPERATOR);
						break;
					case '!':
						clearStack();
						break;
					default:
						break;
				}
				break;
			case MATHOP:
				switch (s[0])	{
					case 's':
						push(sin(pop() * (M_PI/180)), MATHOP);
						printf("\t%.8g\n", pop());
						break;
					case 'c':
						push(cos(pop() * (M_PI/180)), MATHOP);
						printf("\t%.8g\n", pop());
						break;	
					case 'e':
						push(exp(pop()), MATHOP);	
						printf("\t%.8g\n", pop());
						break;
					case 'p':
						double op2 = pop();
						push(pow(pop(),op2), MATHOP);	
						printf("\t%.8g\n", pop());
						break;
					default:
						break;
				}
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("\nerror: unknown command: %s\n",s);
				break;
		}
	}
	return 0;
}