#include <stdio.h>
#include <string.h>

/*
Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than
calling alloc to maintain storage. How much faster is the program?
*/

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

char *lineptr[MAXLINES]; /* pointers to text lines */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

int readlines(char *lineptr[], char *buf);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getline(char *, int);
char *alloc(int);
void swap(char *v[], int i, int j);

/* sort input lines */
int main(void) {
    int nlines; /* number of input lines read */
    char buf[ALLOCSIZE] = {'\0'};
    if ((nlines = readlines(lineptr, buf)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

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
        buf+= len-1;
        if (nlines >= MAXLINES)
            return -1;
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

char *alloc(int n) /* return pointer to n characters */
 {
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else /* not enough room */
        return 0;
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