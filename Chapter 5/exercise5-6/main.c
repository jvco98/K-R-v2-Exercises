#include <inttypes.h>
#include <stdio.h>
#include <string.h>
/*
Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing.

getline (ch 1 / ch 4)
atoi, itoa (ch 2, 3, 4)
reverse (ch 3)
strindex, getop (ch4)
 */

#define MAXLINE 1000 /* maximum input line length */
int getline(char line[], int max);
int strindex(char *source, char *searchfor);
void reverse(char *str, int sign);
void recursive_itoa(int n, char *str, int sign);
void my_itoa(int n, char *str);

int main()
{
    char str[1024] = {'\0'};
    int n = -123456789;
    printf("\n\t\tEnter an integer, pleez :B\t\t\n");
    fflush(stdout);
    //scanf("%i",&n);
    my_itoa(n, str);
    printf("\t\t%s\t\t",str);
    fflush(stdout);
    // ~~~~~~~~~~~~~ reverse tests ~~~~~~~~~~~~~~~
    /*
    char nums[] = "123456789";
    reverse(nums, ((nums[0] - '0') >= 0 && (nums[0] - '0' <= '9') || nums[0] == '+') ? 1 : -1);
    */
    //char line[MAXLINE];
    //char pattern[10] = "is";
    // ~~~~~~~~~~~~~ getline tests ~~~~~~~~~~~~~~~
    /*while (getline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
        else
            printf("character not found\n");*/

    // ~~~~~~~~~~~~~ strindex tests ~~~~~~~~~~~~~~~
    /*
    int res = 0;
    res = strindex("th is a test", pattern);
    if (res >= 0)
        printf("string found at index %d\n", res);
    else
        printf("no match found\n");*/

    return 0;
}

/**
 * Reads a line of input from standard input into the buffer `s` with a limit of `lim` characters.
 * Stops reading after reaching the newline character or the end-of-file.
 *
 * @param s Pointer to the character buffer where the input will be stored.
 * @param lim The maximum number of characters to be read into the buffer, including the null terminator.
 * @return The number of characters read, excluding the null terminator.
 */
int getline(char *s, int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;

    *s = '\0';
    return i;
}

/**
 * Searches for the first occurrence of string `t` within string `s` and returns its starting index.
 * If `t` is not found in `s`, the function returns -1.
 *
 * @param s Pointer to the string in which to search for the substring.
 * @param t Pointer to the substring to be searched for within `s`.
 * @return The starting index of the first occurrence of `t` in `s`, or -1 if `t` is not found.
 */
int strindex(char *s, char *t)
{
    int index = 0, match = 0;
    while (*t != '\0') {t++; match++;} // now at the end of t, stored length of t
    t -= match;
    //while (*s != '\0') {s++; index++;}   // now at the end of s
    int limit = 0;
    while (*s != '\0') {
        char *copyOfS = s;
        char *copyofT = t;
        while (*t != '\0') {
            if (*copyOfS == *copyofT) {
                copyOfS++; copyofT++;
                limit++;
            }
            else if (limit >= match)
                return index;
            else
                break;
        }
        index++;
        limit = 0;
        s++;
    }
    return -1;
}

/**
 * Reverses the content of the given string in-place. Optionally skips the first character
 * if the provided sign is negative.
 *
 * @param str Pointer to the input string to be reversed. The string must be null-terminated.
 * @param sign A flag that determines whether to skip the first character. If negative, the first character is skipped; otherwise, all characters are considered.
 */
void reverse(char *str, int sign) {
    int start = 0, end = 0;

    if (sign < 0)
        start = 1;

    end = strlen(str)-2;
    str += start;

    int front = 0;
    while (str+front < str+end) {
        char temp = *(str+front);
        *(str+front++) = *(str + end);
        *(str+end--) = temp;
    }
}

/**
 * Converts an integer to a null-terminated string representation and stores it in the given buffer.
 * The resulting string will include a leading '-' for negative numbers.
 *
 * @param n The integer to convert to a string.
 * @param str Pointer to the buffer where the resulting string will be stored.
 */
void my_itoa(int n, char *str) {
    int sign = 1;
    if (n < 0) {
        sign = -1;
        n = -n;
        str[0] = '-';
    }
    recursive_itoa(n, str, sign);
    reverse(str, sign);
}

/**
 * Converts an integer to a string recursively and stores the result in the provided character buffer.
 * Handles both positive and negative integers based on the sign parameter.
 *
 * @param n The integer to be converted to a string.
 * @param str Pointer to the character buffer where the converted string will be stored.
 * @param sign Indicates the sign of the integer. A value of -1 represents a negative integer,
 *             and positive integers are represented by 1.
 */
void recursive_itoa(int n, char *str, int sign) {
    static int i = 0;

    if (sign < 0 && i == 0)
        i = 1;

    if (n/10) {
        *(str+(i++)) = n%10 + '0';
        recursive_itoa(n/10, str, sign);
    }
    else
        *(str+i) = n%10 + '0';
}
