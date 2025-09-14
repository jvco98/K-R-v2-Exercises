/*
	Exercise 4-4. Add the commands to print the top elements of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack.  

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void showTop(void);
void clearStack(void);
void duplicate(void);
void swapItems(void);

int main()	{
	int type;
	double op2;
	char s[MAXOP];

	/*
	Exercise 4-4. Add the commands to print the top elements of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack.  
	 */

	while ((type = getop(s)) != EOF)	{
		switch (type)	{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				if (op2 != 0.0)	{
					op2 = pop();
					push(pop() / op2);
				}
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)	{
					push(fmod(pop(), op2));
				}
				else
					printf("error: zero divisor\n");
				break;
			case '?':
				showTop();
				break;
			case '#':
				duplicate();
				break;
			case '~':
				swapItems();
				break;
			case '!':
				clearStack();
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

void duplicate(void) {
	if (sp > MAXVAL-1)
		printf("error: stack is full.\n");
	else
	{	
		double temp = pop();
		push(temp);
		push(temp);
	}
}

void swapItems(void) {
	double item1 = pop();
	double item2 = pop();

	push(item1);
	push(item2);
}

void push(double f)	{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)	{
	if (sp > 0)
		return val[--sp];
	else 	{
		printf("error: stack empty\n");
		return 0.0;
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
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
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
