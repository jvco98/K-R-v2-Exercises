#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Exercise 5-14: Modify the sort program to handle a -r flag, which indicates sorting in reverse
(decreasing) order. Be sure that -r works with -n.
*/

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLEN 1000 // max length of any input line

char *lineptr[MAXLINES]; /* pointers to text lines */

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
void swap(void *v[], int i, int j);
int readlines(char *lineptr[], char *buf);
void writelines(char *lineptr[], int nlines);
int getline(char *, int);
int my_strcmp(char *s, char *t);
int strcmp_reverse(char *s, char *t);
int numcmp_reverse(char *s, char *t);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    int numeric = 0;    /* 1 if numeric sort */
    int reverse = 0;    /* 1 if reverse sort */
    char buf[ALLOCSIZE] = {'\0'};

    if (argc > 1)
        for (int i = 1; argv[i] != NULL; i++)
            if (strcmp(argv[i], "-r") == 0)
                reverse = 1;
            else if (strcmp(argv[i], "-n") == 0)
                numeric = 1;

    if ((nlines = readlines(lineptr, buf)) > 0) {
        if (reverse)
            my_qsort((void**) lineptr, 0, nlines-1, (int (*)(void*, void*))(numeric ? numcmp_reverse : strcmp_reverse));
        else
            my_qsort((void**) lineptr, 0, nlines-1, (int (*)(void*, void*))(numeric ? numcmp : my_strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: no lines read\n");
        return 1;
    }
    return 0;
}

/* qsort: sort v[left]....v[right] into increasing order */
void my_qsort(void *v[], int left, int right,  int (*comp)(void *, void *)) {
    int i, last;

    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    my_qsort(v, left, last-1, comp);
    my_qsort(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
        buf+= len;
        if (nlines >= MAXLINES)
            return -1;
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
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

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int my_strcmp(char *s, char *t)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

/* strcmp_reverse: return >0 if s<t, 0 if s==t, <0 if s>t */
int strcmp_reverse(char *s, char *t) {
    return -my_strcmp(s,t);
}

/* numcmp_reverse: return >0 if s<t, 0 if s==t, <0 if s>t */
int numcmp_reverse(char *s, char *t) {
    return -numcmp(s,t);
}