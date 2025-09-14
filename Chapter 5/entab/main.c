#include <stdio.h>

#define TAB_STOP 8

void entab(int TAB_STOPS);
int main(void) {
    printf("Hello, World!\n");
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
                if (blanks >= TAB_STOPS/2) {
                    putchar('\t');
                } else {
                    // Output accumulated spaces as dots
                    for (int i = 0; i < blanks; i++)
                        putchar('.');
                }
                blanks = 0;
            }
            pos++;
        } else {
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
