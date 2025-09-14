#include <stdio.h>
#include <stdlib.h>

void unescape(char from[], char * to);
void escape(char from[], char * to);

int main(void)
{
    int i;
    char c, s[1024], t[1024];
    
    i = 0;
    while ((c = getchar()) != EOF)
        t[i++] = c;
    t[i] = '\0';
    
    escape(t, s);
    printf("\n%s\n", s);
    unescape(s, s);
    printf("\n%s\n", s);

    return EXIT_SUCCESS;
}

/// @brief Copies string 'from' into string 'to' with escape characters explicitly shown as visible characters
/// @param from String to be copied from 
/// @param to String to be copied to
void escape(char from[], char to[])
{
    int i, j;
    for (i = j = 0; from[i] != '\0'; ++i)
    {
        switch(from[i])
        {
            case '\n':  
                to[j++] = '\\';
                to[j++] = 'n';
                break;
            case '\t':
                to[j++] = '\\';
                to[j++] = 't'; 
                break;
            default:
                to[j++] = from[i];
                break;
        }
    }
    to[j] = '\0';
}

/// @brief Copies string 'from' into string 'to' with hidden escape characters 
/// @param from String to be copied from 
/// @param to String to be copied to
void unescape(char from[], char to[])
{
    int i, j;
    for (i = j = 0; from[i] != '\0'; ++i)
    {
        switch(from[i])
        {
            case '\\':
                if (from[i+1] == 'n')
                {
                    i++;
                    to[j++] = '\n';
                }
                else if(from[i+1] == 't')
                {
                    i++;
                    to[j++] = '\t';
                }
                else
                    to[j++] = from[i];
                break;
            default:
                to[j++] = from[i];
                break;
        }
    }
    to[j] = '\0';
}