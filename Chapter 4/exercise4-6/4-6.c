/*
	Exercise 4-6: Add commands for handling variables. (It's easy to provide twnty-six variables with single-letter names). Add a variable for the most recently printed value.
*/

#include <stdio.h>	
#include <stdlib.h>	
#include <ctype.h>	
#include <math.h>	
#include <string.h>
#include <stdbool.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define VARIABLE '1'
#define MATHOP '2'
#define OPERATOR '3'
#define CMD '4'

int sp = 0;
double val[MAXVAL];		// stack for numbers and variables
int valType[MAXVAL];	// parallel stack to val[] to keep track of what type of value is in the stack
char vars[26] = {0};	// 26 variables, a-z
char buf[BUFSIZE];
int bufp = 0;

int getop(char []);
void push(double, int);
double pop(void);
int getch(void);
void ungetch(int);
void showTop(void);
void clearStack(void);
void duplicate(int type);
void swapItems(int type);
double resolveOperand(double operand, bool isVar);

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
				push(s[0]-'a', VARIABLE);	// push the variable index onto the stack
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
								push(resolveOperand(op1, op1_isvar) / resolveOperand(op2, op2_isvar), NUMBER);
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

void clearStack(void) {
	sp = 0;
}

void duplicate(int type) {
	if (sp > MAXVAL-1)
		printf("error: stack is full.\n");
	else
	{	
		int val_type = valType[sp];
		double temp = pop();
		push(temp, val_type);
		push(temp, val_type);
	}
}

void swapItems(int type) {
	double item1 = pop();
	double item2 = pop();

	push(item1, type);
	push(item2, type);
}

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

int getch(void)	{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)	{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void showTop(void) {
	if (sp > 0)
		printf("top of stack: %8g\n", val[sp-1]);
	else
		printf("stack is empty\n");
}

int getop(char s[])	{
	int i, c, sign = 0;

	/* skip whitespace */
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';

	/*if (i == 0 && c == '-') {
		sign = -1;
		c = getch();
	}*/
	
	/* look for variable, operator, mathop */
	if (!isdigit(c) && c != '.')
	{
		
		if (c == '\n' || c == ' ' || c == '\t')	/* found whitespace */
			return c;
		else if (ispunct(c))	/* found non alphanumeric character (cmd or operator) */
		{
			if (c <= '/' && c >= '%' || c == '=') // found operator
			{
				return OPERATOR;
			}
			if (c <= '$' && c >= '!') // found operator
			{
				return CMD;
			}

			printf("\nerror: unknown command: %c\n",c);
			return -1;
		}
		else {	
			// check for variable
			char temp = getch();
			if ((temp == ' ') || (temp == '\n') || (temp == '\t'))	// found variable
				return VARIABLE;
			else 
			{
				char str[5];
				int k=0;
				str[k++] = c;
				str[k++] = temp;

				// get next 2 char, check for mathop
				while(isalpha((str[k++] = getchar()))) {;}
				str[k] = '\0';

				if (strcmp(str, "cos\n") == 0)
					return MATHOP;
				else if (strcmp(str, "sin\n") == 0)
					return MATHOP;
				else if (strcmp(str, "exp\n") == 0)
					return MATHOP;
				else if (strcmp(str, "pow\n") == 0)
					return MATHOP;
				else
				{
					printf("unknown command: %s", str);
					return '\n';
				}
			}
		}
	}
	
	/* get number */
	i = 0;
	if (c == '-') 	{
		s[i] = c;
		if (!isdigit(c = getch()))	{
			return '-';
		}
		else
			s[++i] = c;
	}
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));
	if (c == '.')
		while (isdigit(s[++i] = c = getch()));

	s[i] = '\0';
	//printf("%s\n", s);
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

double resolveOperand(double operand, bool isVar)
{
	return isVar ? vars[(int)operand] : operand;	// return the value of the variable
}