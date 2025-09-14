#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Exercise 5-16: Add the -d ("directory order") option, which makes comparisons only on letters, numbers, and blanks.
Make sure it works in conjunction with -f.
*/

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */
#define MAXLEN 1000 // max length of any input line

char *lineptr[MAXLINES]; /* pointers to text lines */

void my_qsort(void *lineptr[], int left, int right, int order, int (*comp)(void *, void *));
void swap(void *v[], int i, int j);
int readlines(char *lineptr[], char *buf);
void writelines(char *lineptr[], int nlines);
int getline(char *, int);

int my_strcmp(char *s, char *t);
int strcmp_insensitive(char *s, char *t);
int strcmp_reverse(char *s, char *t);

int numcmp(char *, char *);
int numcmp_reverse(char *s, char *t);

int dir_cmp(char *s, char *t);
int dircmp_insensitive(char *s, char *t);
int dir_cmp_helper(char *s, char *t, int sensitive);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;             /* number of input lines read */
    int numeric = 0;        /* 1 if numeric sort */
    int order = 1;          /* -1 if reverse sort */
    int fold = 0;           /* 1 if fold sort */
    int directory = 0;      /* 1 if directory order */
    char buf[ALLOCSIZE] = {'\0'};

    /* COMMAND LINE ARG PARSING */
    if (argc > 1)
        for (int i = 1; argv[i] != NULL; i++)
            if (strcmp(argv[i], "-r") == 0)
                order = -1;
            else if (strcmp(argv[i], "-n") == 0)
                numeric = 1;
            else if (strcmp(argv[i], "-d") == 0)
                directory = 1;
            else if (strcmp(argv[i], "-f") == 0)
                fold = 1;

    if (numeric && fold) {
        printf("numeric and fold flags received... ignoring -f\n");
        fflush(stdout);
        fold = 0;
    }

    int (*comparison_function)(void *, void*);

    if (numeric)
        comparison_function = (int (*)(void*, void*))numcmp;
    else if (directory & fold)
        comparison_function = (int (*)(void*, void*))dircmp_insensitive;
    else if (directory)
        comparison_function = (int (*)(void*, void*))dir_cmp;
    else if (fold)
        comparison_function = (int (*)(void*, void*))strcmp_insensitive;
    else
        comparison_function = (int (*)(void*, void*))my_strcmp;

    if ((nlines = readlines(lineptr, buf)) > 0) {
        my_qsort((void**) lineptr, 0, nlines-1, order, comparison_function);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: no lines read\n");
        return 1;
    }
    return 0;
}

/* qsort: sort v[left]....v[right] into increasing order */
void my_qsort(void *v[], int left, int right, int order, int (*comp)(void *, void *)) {
    int i, last;

    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (order*((*comp)(v[i], v[left])) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    my_qsort(v, left, last-1, order, comp);
    my_qsort(v, last+1, right, order, comp);
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
int my_strcmp(char *s, char *t) {
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int strcmp_insensitive(char *s, char *t) {
    for ( ; tolower(*s) == tolower(*t); s++, t++)
        if (tolower(*s) == '\0')
            return 0;
    return tolower(*s) - tolower(*t);
}

/**
 * Compares two strings in a directory order considering only alphanumeric
 * characters and spaces, while being case-sensitive.
 *
 * This function uses a helper function `dir_cmp_helper` with a flag that ensures
 * case-sensitive comparison of the provided strings.
 *
 * @param s Pointer to the first string to be compared.
 * @param t Pointer to the second string to be compared.
 * @return An integer less than, equal to, or greater than zero if the first
 *         string is found, respectively, to be less than, equal to, or greater
 *         than the second string in directory order comparison.
 */
int dir_cmp(char *s, char *t) {
    return dir_cmp_helper(s, t, 0);
}

/**
 * Compares two strings in a directory order, ignoring case sensitivity.
 *
 * This function utilizes a helper function `dir_cmp_helper` with a flag
 * to perform case-insensitive comparisons of the strings.
 *
 * @param s Pointer to the first string to be compared.
 * @param t Pointer to the second string to be compared.
 * @return An integer less than, equal to, or greater than zero if the first
 *         string is found, respectively, to be less than, equal to, or greater
 *         than the second string, using directory order and case-insensitive comparison.
 */
int dircmp_insensitive(char *s, char *t) {
    return dir_cmp_helper(s, t, 1);
}


/**
 * Compares two strings in directory order, considering alphanumeric characters
 * and spaces, with an option for case-sensitive or case-insensitive comparison.
 *
 * This helper function performs a character-by-character comparison of the two
 * input strings, skipping over non-alphanumeric characters and spaces. It
 * determines the sorting order based on the provided sensitivity flag.
 *
 * @param s Pointer to the first string to be compared.
 * @param t Pointer to the second string to be compared.
 * @param sensitive An integer flag indicating whether the comparison should
 *                  be case-sensitive (non-zero) or case-insensitive (zero).
 * @return An integer less than, equal to, or greater than zero if the first
 *         string is found, respectively, to be less than, equal to, or greater
 *         than the second string in directory order comparison.
 */
int dir_cmp_helper(char *s, char *t, int sensitive) {
    /* SKIP TO ALPHANUMERIC CHARACTER */
    while(*s != '\0' && !isalnum(*s) && *s != ' ')
        s++;
    while(*t != '\0' && !isalnum(*t) && *t != ' ')
        t++;

    /* COMPARE CHARACTER BY CHARACTER */
    while (*s != '\0' && *t != '\0') {
        char x, y;
        if (sensitive) {
            x = tolower(*s);
            y = tolower(*t);

            if(x != y)
                return x - y;            /* RETURN FINAL COMPARISON */
        } else {
            if(*s != *t)
                return *s - *t;            /* RETURN FINAL COMPARISON */
        }

        s++; t++;
        /* CONTINUE COMPARISON, SKIP TO ALPHANUMERIC CHAR */
        while(*s != '\0' && !isalnum(*s) && *s != ' ')
            s++;
        while(*t != '\0' && !isalnum(*t) && *t != ' ')
            t++;
    }

    /* REACHED END OF AT LEAST ONE STRING */
    if (*s == '\0' && *t == '\0')
        return 0;
    else if (*s == '\0')
        return -1;
    else
        return 1;
}


