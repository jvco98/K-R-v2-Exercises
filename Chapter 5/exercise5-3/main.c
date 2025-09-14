#include <stdio.h>
/*
Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s

Reference :
strcat: concatenate t to end of s; s must be big enough
 void strcat(char s[], char t[])
 {
     46
     int i, j;
     i = j = 0;
     while (s[i] != '\0') // find end of s
         i++;
     while ((s[i++] = t[j++]) != '\0') // copy t
         ;
 }
*/
void strcat(char *s, char *t);

int main(void) {
    char x[20] = "hello\0";
    char y[] = "there\0";
    strcat(x, y);
    printf("%s", x);
    fflush(stdout);
    return 0;
}
///strcat: concatenate t to end of s; s must be big enough
void strcat(char *s, char *t) {
    while (*s++ != '\0')
        ;
    // now at end of s

    while (*s++ = *t++)
        ;
}
