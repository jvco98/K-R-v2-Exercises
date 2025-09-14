#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void my_itoa(int n, char str[]);
void recursive_itoa(int n, char str[], int sign);
void reverse(char str[], int sign);

int main(void) {
    char str[1024];
    int n = -123456789;
    printf("\n\t\tEnter an integer, pleez :B\t\t\n");
    scanf("%i",&n);
    my_itoa(n, str);
    printf("\t\t$c\t\t",str);
    fflush(stdout);
    return 0;
}

void my_itoa(int n, char str[]) {
    int sign = 1;
    if (n < 0) {
        sign = -1;
        n = -n;
        str[0] = '-';
    }
    recursive_itoa(n, str, sign);
    reverse(str, sign);
}

///recursive_itoa: recursive approach to itoa
void recursive_itoa(int n, char str[], int sign) {
    static int i = 0;

    if (sign < 0 && i == 0)
        i = 1;

    if (n/10) {
        str[i++] = n%10 + '0';
        recursive_itoa(n/10, str, sign);
    }
    else {
        str[i++] = n%10 + '0';
        str[i] = '\0';
    }
}

///reverse: reverses input string s (helper for recurseive__itoa)
void reverse(char str[], int sign) {
    int start = 0, end = 0;

    if (sign < 0)
        start = 1;

    for (int i = start; str[i] != '\0'; i++)
        end++;

    for (int i = start; i < end; i++) {
        char temp = str[i];
        str[i] = str[end];
        str[end--] = temp;
    }
}