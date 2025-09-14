/*
 * Exercise 5-11. Modify the program entab and detab (written as exercises in Chapter 1) to
 * accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.
 */

#include <stdio.h>
#include <string.h>

#define NUMBER '0'
#define OPERATOR '1'
#define MAXLINE 1000
#define STACKMAX 100

int stack[STACKMAX];
int stacktype[STACKMAX];


int getline(char *line, int max);
void entab(int TAB_STOPS);
void detab(int TAB_STOPS);



int main(int argc, char *argv[])
{
    int TAB_SIZE = 4;
    while (--argc > 0) {
        TAB_SIZE = (++argv)[0][0] - '0';
    }
    entab(TAB_SIZE);
    detab(TAB_SIZE);
    return 0;
}

void entab(int TAB_STOPS) {
    int pos = 0;        // Current position in line
    int blanks = 0;     // Count of consecutive blanks
    int c;              // Input character

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blanks++;
            
            // Check if next position will be a tab stop
            if ((pos + 1) % TAB_STOPS == 0) {
                // If we have enough spaces, output a tab
                if (blanks >= TAB_STOPS) {
                    putchar('\t');
                } else {
                    // Output accumulated spaces as dots
                    for (int i = 0; i < blanks; i++)
                        putchar('.');
                }
                blanks = 0;
            }
            pos++;
        }
        else {
            // Output any remaining spaces before non-space character
            while (blanks > 0) {
                putchar('.');
                blanks--;
            }

            
            putchar(c);
            fflush(stdout);

            if (c == '\n') {
                pos = 0;
            } else if (c == '\t') {
                // Move position to next tab stop
                pos = pos + (TAB_STOPS - (pos % TAB_STOPS));
            } else {
                pos++;
            }
        }
    }
    while (blanks > 0) {
        putchar('.');
        blanks--;
    }

}


void detab(int TAB_STOPS) {
    int i = 0, c;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (int blanks = TAB_STOPS - (i % TAB_STOPS); blanks > 0; blanks--) {
                putchar(' ');
                i++;
            }
        }
        else if (c == '\n') {
            putchar('\n');
            i = 0;
        }
        else {
            putchar(c);
            i++;
        }
        fflush(stdout);
    }
}