#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/* 
	Exercise 1-24: Write a program to check a C program for rudimentary syntax 
	errors like unbalanced parenthesis, brackets and braces. Don't forget about
	quotes, both single and double, escape sequences, and comments. (This program
	is hard if you do it in full generality)
*/

#define MAX 100

// define the stack
typedef struct
{
	char items[MAX];
	int top;
} Stack;


// initialize the stack
void initStack(Stack* s)
{
	s->top = -1;
}	

// check if stack is empty
bool isEmpty(Stack* s)
{
	return (s->top == -1);
}

// check if stack is full
bool isFull(Stack* s)
{
	return (s->top == MAX-1);
}

// push item onto the stack
void push(Stack* s, char item)
{
	if (isFull(s))
	{
		printf("stack overflow\n");
		return;
	}
	s->items[++s->top] = item;
}

// get and remove top item from stack
char pop(Stack* s)
{
	if (isEmpty(s))
	{
		printf("stack underflow\n");
		exit(1);
	}
	return s->items[s->top--];
}

// get top item from stack
char peek(Stack* s)
{
	if (isEmpty(s))
	{
		printf("stack is empty\n");
		exit(1);
	}
	return s->items[s->top];
}

// get an items counterpart
char counterpart(char s)
{
	switch(s)
	{
    	case '<': return '>';
    	case '[': return ']';
    	case '(': return ')';
    	case '{': return '}';
    	case '"': return '"';
    	case '\'': return '\'';
    	default: return '\0';	// Handle unresolved cases
	}
}

/*
what happens when 
*/

int main()
{
	// Initialize data
	Stack stack;
	initStack(&stack);

	bool inQuote, inDQuote, inComment, inMLComment;
	inQuote = inDQuote = inComment = inMLComment = false;
	char c, lastChar;
	
	// Main loop
	while( (c = getchar()) != EOF )
	{
		// ~~~~~~~~~~~~ STATE MACHINE ~~~~~~~~~~~~~~~~~~
		// Decides flow of control, if in comment, ignores inputs
		if (c == '\n' && inComment)
			inComment = false;
		if (c == '/' && lastChar == '*' && inMLComment) 
			inMLComment = false;
		if (c == '*' && lastChar == '/')
        {
			inMLComment = true;
            lastChar = c;
        }
		if (inComment || inMLComment)
			continue;
		// ~~~~~~~~~~~~ STATE MACHINE ~~~~~~~~~~~~~~~~~~

		switch (c)
		{
			// Look for characters of interest
			// If token found, push to stack
			// If token matched, take token off stack
			case '\'':
				if ( inQuote  )
				{
					if ( (peek(&stack) == '\'') )
					{
						inQuote = false;
						pop(&stack);
					}
					else
					{
                        printf("Did you forget a '%c' somewhere?\n", counterpart(stack.items[stack.top]));
					    return 1;
                    }
				}
				else 
				{
					//printf("opening quote found!!\n");
					inQuote = true;
					push(&stack, c);
				}
				break;
			case '"':
				if ( inDQuote  )
				{
					if ( (peek(&stack) == '"') )
					{
						//printf("closing d-quote found!!\n");
						inDQuote = false;
						pop(&stack);
					}
					else
					{
                        printf("Did you forget a '%c' somewhere?\n", counterpart(stack.items[stack.top]));
					    return 1;					
                    }
				}
				else 
				{
					//printf("opening d-quote found!!\n");
					inDQuote = true;
					push(&stack, c);
				}
				break;
			case '(':
				push(&stack, c);
				break;
			case ')':
				if (peek(&stack) == '(') 
					pop(&stack);
				else
				{
					printf("Did you forget a '%c' somewhere?\n", counterpart((stack.items[stack.top])));
					return 1;
				}
				break;
			case '{':
				push(&stack, c);
				break;
			case '}':
				if (peek(&stack) == '{') 
					pop(&stack);
				else
				{
					printf("Did you forget a '%c' somewhere?\n", counterpart((stack.items[stack.top])));
					return 1;
				}
				break;
			case '[':
				push(&stack, c);
				break;
			case ']':
				if (peek(&stack) == '[') 
					pop(&stack);
				else
				{
					printf("Did you forget a '%c' somewhere?\n", counterpart(stack.items[stack.top]));
					return 1;
				}
				break;
			case '<':
				push(&stack, c);
				break;
			case '>':
				if (peek(&stack) == '<') 
					pop(&stack);
				else
				{
					printf("Did you forget a '%c' somewhere?\n", counterpart(stack.items[stack.top]));
					return 1;
				}
				break;
			case '/':
				if (!inComment && lastChar == '/')
					inComment = true;
				break;
		}
		lastChar = c;
	}

	// Once end of loop is reached, we're expecting an empty stack.
	if (!isEmpty(&stack))
	{
		printf("something is not right...\n '%c' sits on top of stack... did you miss a '%c' somewhere?\n",stack.items[stack.top], counterpart(stack.items[stack.top]));
		return 1;
	}
    else   
        printf("looks good!\n");
	return 0;
}