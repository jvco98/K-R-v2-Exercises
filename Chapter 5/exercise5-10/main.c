/*Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument. For example,
 expr 2 3 4 + *
evaluates 2 * (3+4). */

#include <stdio.h>
#include <string.h>

#define NUMBER '0'
#define OPERATOR '1'
#define MAXLINE 1000
#define STACKMAX 100

int stack[STACKMAX];
int stacktype[STACKMAX];


int getline(char *line, int max);
void push(int val, int type);
int pop(void);
int stackp = 0;

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    char c;
    double op2 = 0;

    while (--argc > 0 && (c = *(++argv)[0])) {
        switch (c) {
            case '0'...'9':
                push(c-'0', NUMBER);
                break;
            case '*':
                push(pop() * pop(), NUMBER);
                break;
            case '/':
                op2 = pop();
                push(pop() / op2, NUMBER);
                break;
            case '+':
                push(pop() + pop(), NUMBER);
                break;
            case '-':
                op2 = pop();
                push(pop() - op2, NUMBER);
                break;
            default:
                printf("find: illegal input %c\n", c);
                argc = 0;
                break;
        }
    }
    if (argc != 0)
        printf("Usage: 2 3 4 + *\n\t(evaluates 2 * (3+4))\n");
    printf("math results in: %d\n", pop());
    return 0;
}

int getline(char *line, int max) {
    char c; int count = 0;
    while ((c=getchar()) != '\n' && count < max && c != EOF) {
        *line++ = c;
        count++;
    }
    *++line = '\0';
    return count;
}

int pop(void) {
    if (stackp > 0)
        return stack[--stackp];
    else {
        printf("stack is empty...\n");
        fflush(stdout);
    }

}

void push(int val, int type) {
    if (stackp >= 0 && stackp < STACKMAX) {
        stack[stackp] = val;
        stacktype[stackp++] = type;
    }
    else
        printf("stack pointer out of range... likely full\n");
}