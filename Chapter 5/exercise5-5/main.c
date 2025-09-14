#include <stdio.h>

/*
Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.

char *strncpy(s,ct,n): copy at most n characters of string ct to s; return s. Pad with '\0''s
if ct has fewer than n characters.

char *strncat(s,ct,n): concatenate at most n characters of string ct to string s, terminate s
with '\0'; return s.

int strncmp(cs,ct,n): compare at most n characters of string cs to string ct; return <0 if
cs<ct, 0 if cs==ct, or >0 if cs>ct
*/

void strncpy(char *s, char *ct, int n);
void strncat(char *s, char *ct, int n);
int strncmp(char *cs, char *ct, int n);

int main(void) {
    char asd[8] = "naois";
    char qwe[] = "nowisnow";

    /*
    char c1[] = "123asd";
    char c2[] = "12onetwo";

    printf("%s\n", asd);
    fflush(stdout);
    strncpy(asd, qwe, 3);
    printf("%s\n", asd);
    fflush(stdout);
    */
    /*
    int result = strncmp(c1, c2, 2);
    if (result < 0)
        printf("c1 and c2 don't match at least %d characters.. c1 > c2\n", 2);
    else if (result > 0)
        printf("c1 and c2 don't match at least %d characters.. c1 < c2\n", 2);
    else
        printf("first %d characters of c1 and c2 match\n", 2);
    */
    strncat(asd, qwe, 3);
    printf("%s\n", asd);
    fflush(stdout);
    return 0;
}

void strncpy(char *s, char *ct, int n) {
    char *temp = ct;

    while (n > 0 && *ct != '\0') {
        *s++ = *ct++;
        n--;
    }
    while (n > 0) {
        *s++ = '\0';
        n--;
    }
}

int strncmp(char *cs, char *ct, int n) {
    while ((*cs == *ct) && n > 0)
        n--;

    while (n > 0)    //less than n matching characters were found
        return (*cs > *ct) ? 1 : -1;

    return 0;
}

void strncat(char *s, char *ct, int n) {
    while (*s != '\0') {
        s++;
    }
    //reached end of s
    while (n > 0) {
        *s++ = *ct++;
        n--;
    }
    *s = '\0';
}