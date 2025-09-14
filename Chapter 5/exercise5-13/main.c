#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*
Exercise 5-13. Write the program tail, which prints the last n lines of its input. By default, n
is set to 10, let us say, but it can be changed by an optional argument so that
 tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the
input or the value of n. Write the program so it makes the best use of available storage; lines
should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
fixed size.
*/

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

char *lineptr[MAXLINES]; /* pointers to text lines */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

int readlines(char *lineptr[], char *buf);
void writelines(char *lineptr[], int nlines, int last_lines);
int getline(char *, int);

int main(int argc, char *argv[])
{
    int nlines; /* number of input lines read */
    char buf[ALLOCSIZE] = {'\0'};
    if ((nlines = readlines(lineptr, buf)) > 0) {
        int last_nlines = nlines; /* number of last n lines to write */
        //if command line arguments present, use supplied arguments
        if (--argc > 0) {
            argv++;
            if ( argv[0][0] == '-' && isdigit(argv[0][1]) ) {
                if  (argv[0][1]-'0' > nlines)
                    printf("value provided exceeds number of lines read... default number of last lines to print: %d\n\n", argv[0][1]-'0', nlines, nlines);
                else
                    last_nlines = argv[0][1]-'0';
            }
            else {
                printf("intended format: '-n' to print the last 'n' lines entered\n");
                return -1;
            }
        }
        writelines(lineptr, nlines, last_nlines);
        return 0;
    } else {
        printf("error: no lines read\n");
        return 1;
    }
    return 0;
}

#define MAXLEN 1000 // max length of any input line
int getline(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], char *buf) {
    int len, nlines, nchars;
    char *b = buf;
    char *bufmax = buf + ALLOCSIZE, line[MAXLEN];

    nlines = 0; nchars = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        line[len-1] = '\0'; /* delete newline */
        strcpy(buf, line);
        lineptr[nlines++] = buf;
        buf+= len;
        if (nlines >= MAXLINES)
            return -1;
    }
    return nlines;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int last_lines) {
    int skip = nlines - last_lines;
    while (skip-- > 0)
        *lineptr++;
    while (last_lines-- > 0) {
        printf("%s\n", *lineptr++);
        fflush(stdout);
    }
}

int getline(char *s, int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        *(s + i++) = c;
    if (c == '\n')
        *(s+i++) = c;

    *(s+i) = '\0';
    return i;
}