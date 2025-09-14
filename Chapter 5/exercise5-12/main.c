/*
 *Exercise 5-12. Extend entab and detab to accept the shorthand
 *entab -m +n
 *to mean tab stops every n columns, starting at column m. Choose convenient (for the user)
 *default behavior.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define NUMBER '0'
#define OPERATOR '1'
#define MAXLINE 1000
#define STACKMAX 100

int stack[STACKMAX];
int stacktype[STACKMAX];

int getline(char *line, int max);
void entab(int START, int TAB_STOPS);
void detab(int START, int TAB_STOPS);

int main(int argc, char *argv[])
{
    int TAB_SIZE = 4;
    int START_POS = 0;
    int start_pos_count = 1;
    //if command line arguments present, use supplied arguments
    if (--argc > 0) {
        argv++;
        if (argv[0][0] == '-'  &&  isdigit(argv[0][start_pos_count])) {
            char *arg1 = argv[0];
            char asd[5];
            strcpy(asd, argv[0]);
            int z = 1;
            while (isdigit(asd[z])) {
                printf("%c", asd[z++]);
                fflush(stdout);
            }
            START_POS = argv[0][1]-'0';
            printf("start tab mods at columns %d\n", START_POS);
            fflush(stdout);
            if (argv[1][0] == '+' &&  isdigit(argv[1][1])) {
                TAB_SIZE = (argv)[1][1] - '0';
                printf("new tab stops: %d\n", argv[1][1]-'0');
                fflush(stdout);
            }
            else {
                printf("intended format: '-m +n' to mean tab stops every n columns, starting at column m.");
                return -1;
            }
        }
        else {
            printf("intended format: '-m +n' to mean tab stops every n columns, starting at column m.");
            return -1;
        }
    }
    //entab input
    entab(START_POS, TAB_SIZE);
    //detab input
    //detab(START_POS, TAB_SIZE);
    return 0;
}

void entab(int START, int TAB_STOPS) {
    int pos = 0;        // Current position in line
    int blanks = 0;     // Count of consecutive blanks
    int c;              // Input character

    while ((c = getchar()) != EOF && START-- > 0) {
        if (c == ' ') {
            putchar('.');
            pos++;
        }
        else {
            putchar(c);
            pos++;
        }
    }
    putchar(c);
    fflush(stdout);
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


void detab(int START, int TAB_STOPS) {
    int i = 0, c;
    while ((c = getchar()) != EOF && START-- > 0) {
        if (c == ' ') {
            putchar('.');
            i++;
        }
        else {
            putchar(c);
            i++;
        }
    }
    putchar(c);
    fflush(stdout);
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