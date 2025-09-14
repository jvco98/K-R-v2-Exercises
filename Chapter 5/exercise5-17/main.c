#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Exercise 5-17: Add a field-searching capability, so sorting may be done on fields within lines, each
field sorted according to an independent set of options.
*/

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

#define OPT_REVERSE (1 << 0)    // 0b0001
#define OPT_NUMERIC (1 << 1)    // 0b0010
#define OPT_DIRECTORY (1 << 2)  // 0b0100
#define OPT_FOLD (1 << 3)       // 0b1000

#define MAX_FIELDS 1024         // max number of possible fields to add sorting conditions to
#define MAX_SORT_FIELDS 10      // max number of sorting rules we can handle

char *lineptr[MAXLINES]; /* pointers to text lines */

typedef struct {
    int field_num;
    uint8_t options;
} FIeldSort;

FIeldSort field_sorts[MAX_FIELDS] = {0};
int field_index = 0;
int field_count = 0;

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
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

int master_compare(char *lineA, char *lineB);
void extract_field(char **start, char **end, int n);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;             /* number of input lines read */
    char buf[ALLOCSIZE] = {'\0'};
    int order = 1;
    // holds options for each field
    // bits 7-4 = field 1 // bits 3-0 = field 2
    uint8_t field_options = 0;

    /* COMMAND LINE ARG PARSING */
    if (argc == 0)
        printf("no arguments... basic line sort...?\n");
    else if (argc > 1) {
        /* parse command line for field options */
        while (++argv && *argv != NULL) {
            if (strncmp(*argv, "-k",2) == 0) {
                int temp = 0;
                char *p = *argv + 2;
                while (isdigit(*p)) {
                    temp = (temp * 10) + (*p - '0');
                    p++;
                }

                field_sorts[field_index].field_num = temp;

                // do stuff for option bits next
                int max_fields = 4;
                while (*p != '\0' && isalpha(*p) && max_fields-- > 0) {
                    switch (*p) {
                        case 'r':
                            field_sorts[field_index].options |= OPT_REVERSE;
                            break;
                        case 'n':
                            field_sorts[field_index].options |= OPT_NUMERIC;
                            break;
                        case 'd':
                            field_sorts[field_index].options |= OPT_DIRECTORY;
                            break;
                        case 'f':
                            field_sorts[field_index].options |= OPT_FOLD;
                            break;
                        default:
                            printf("field option not recognized... expected 'r', 'n', 'd', or 'f'...\n");
                            return 1;
                    }
                    p++;
                }
                field_index++;
            } else {
                printf("incorrect format... expected '-k'...\n");
                return 1;
            }
        }
    }
    int (*comparison_function)(void *, void*) = (int (*)(void*, void*))master_compare;

    if ((nlines = readlines(lineptr, buf)) > 0) {
        my_qsort((void**) lineptr, 0, nlines-1, comparison_function);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: no lines read\n");
        return 1;
    }
}

/* qsort: sort v[left]....v[right] into increasing order */
void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {

    if (left >= right)  /* do nothing if the array contains */
        return;
    swap(v, left, (left+right)/2);
    int last = left;
    for (int i = left+1; i <= right; i++)
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
int my_strcmp(char *s, char *t) {
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int master_compare(char *lineA, char *lineB) {
    int result;
    for (int i = 0; i < field_index; i++) {
        /* pointers are reset to the start of the line for each new field rule */
        char *fieldA = lineA, *fieldA_end, *fieldB = lineB, *fieldB_end;

        /* pass the ADDRESS of the pointers so the function can change them */
        extract_field(&fieldA, &fieldA_end, i);
        extract_field(&fieldB, &fieldB_end, i);

        /* temporarily terminate the fields to treat the as separate strings */
        char A_original = *fieldA_end;
        char B_original = *fieldB_end;
        *fieldA_end = '\0';
        *fieldB_end = '\0';

        // !! ready to do comparison !!
        uint8_t current_options = field_sorts[i].options;

        int numeric = 0, order = 1, fold = 0, directory = 0;

        if (current_options & OPT_FOLD)
            fold = 1;
        if (current_options & OPT_NUMERIC)
            numeric = 1;
        if (current_options & OPT_DIRECTORY)
            directory = 1;
        if (current_options & OPT_REVERSE)
            order = -1;

        if (numeric)
            result = numcmp(fieldA, fieldB);
        else if (directory & fold)
            result = dircmp_insensitive(fieldA, fieldB);
        else if (directory)
            result = dir_cmp(fieldA, fieldB);
        else if (fold)
            result = strcmp_insensitive(fieldA, fieldB);
        else
            result = my_strcmp(fieldA, fieldB);

        /* remove temporary null terminator */
        *fieldA_end = A_original;
        *fieldB_end = B_original;

        /* if a difference was found, return the result immediately */
        if (result != 0)
            return order*result;
    }
    /* if all fields were equal, return 0 */
    return 0;
 }

void extract_field(char **start, char **end, int n) {
    /* create a local copy to work with */
    char *p = *start;
    int field_no = 0;

    while (*p != '\0') {

        /* move to the start of the next field */
        while (isblank(*p))
            p++;

        /* if we're at the end of the string, stop */
        if (*p == '\0')
            break;

        field_no++;

        /* if we found our target field, break the search */
        if (field_no == field_sorts[n].field_num)
            break;

        /* otherwise, skip this field and continue searching */
        while (!isblank(*p) && *p != '\0')
            p++;
    }

    // update the caller's pointers with the results
    *start = p;
    *end = p;
    while (!isblank(**end) && **end != '\0')
        (*end)++;
}

int strcmp_insensitive(char *s, char *t) {
    for ( ; tolower(*s) == tolower(*t); s++, t++)
        if (tolower(*s) == '\0')
            return 0;
    return tolower(*s) - tolower(*t);
}

int dir_cmp(char *s, char *t) {
    return dir_cmp_helper(s, t, 0);
}

int dircmp_insensitive(char *s, char *t) {
    return dir_cmp_helper(s, t, 1);
}

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
