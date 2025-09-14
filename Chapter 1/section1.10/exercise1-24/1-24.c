#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
/* 
	Exercise 1-24: Write a program to check a C program for rudimentary syntax 
	errors like unbalanced parenthesis, brackets and braces. Don't forget about
	quotes, both single and double, escape sequences, and comments. (This program
	is hard if you do it in full generality)
*/

#define PARENTHESIS_L '('
#define PARENTHESIS_R ')'
#define CBRACKET_L '{'
#define CBRACKET_R '}'
#define BRACKET_L '['
#define BRACKET_R ']'

bool isOpen(char c);
bool isClosed(char c);

char open[7] = {'{', '(', '[', '\'', '"', '<', '/'};
char close[7] = {'}', ')', ']', '\'', '"', '>', '/'};
bool inDQuote, inQuote;
/*
if (c == balancing character (bracket, quotes, braces, parenthesis))
    get_closure(specific balancing character)

** within get_closure definition **
get_closure(char x)
{
	while((c=getchar() != EOF)
	{
		if (c == balancing character (bracket, quotes, braces, parenthesis))
    		get_closure(specific balancing character)
	}
}
*/

int main()
{
	char c;

	// ( ) , { } , [ ] , < > , ' ' , " " , /* */
	// P = PARENTHESIS
	// B = [ BRACKET ]   |   CB = { CURLY BRACKET }   |   AB = < ANGLED BRACKET >
	// Q = ' QUOTE'      |   DQ = " DOUBLE QUOTE "
	// _L_ = LEFT = OPEN         |   _R_ = RIGHT = CLOSE

	int P_L_CNT = 0, P_R_CNT = 0, CB_L_CNT = 0, CB_R_CNT = 0, B_L_CNT = 0, B_R_CNT = 0, AB_L_CNT = 0, AB_R_CNT = 0, Q_L_CNT = 0, Q_R_CNT = 0, DQ_L_CNT = 0, DQ_R_CNT = 0; 

		inDQuote = inQuote = false;

	while((c = getchar()) != EOF)
	{
		switch (c)
		{
			case '\'':
				if (inQuote)
				{
					Q_R_CNT++;
					inQuote = false;
				}
				else
				{
					Q_L_CNT++;
					inQuote = true;
				}	
				//!inQuote ? inQuote = true : inQuote = false;  	
			case '"':
				if (inDQuote)
				{
					DQ_R_CNT++;
					inDQuote = false;
				}
				else
				{
					DQ_L_CNT++;
					inDQuote = true;
				}	
				//!inDQuote ? inDQuote = true : inDQuote = false;  	
			default:
				//printf("quote open/close count: [%d,%d]\n", QUOTE_OPEN_CNT, QUOTE_CLOSE_CNT);
				continue;
				//printf("dquote open/close count: [%d,%d]\n", DQUOTE_OPEN_CNT, DQUOTE_CLOSE_CNT);
		}


		if (isOpen(c))
			// note it
			printf("open\n");
		else if (isClosed(c))
			// note it
			printf("closed\n");
		else
			continue;
	}

	return 0;
}

bool isOpen(char c)
{
	if (c == '\'')
	{
		if (!inQuote)
		{
			printf("single quote open found\n");
			inQuote = true;
			inDQuote = false;
			return true;
		}
	}
	else if (c == '"')
	{
		if (!inDQuote)
		{
			printf("double quote open found\n");
			inQuote = false;
			inDQuote = true;
			return true;
		}
	}
	else
	{
		inQuote = false;
		inDQuote = false;
		return false;
	}
}

bool isClosed(char c)
{
	for (int i = 0; i < 7; ++i)
		if (c == close[i])
			printf("close[%d] = %c\n", i, close[i]);
}