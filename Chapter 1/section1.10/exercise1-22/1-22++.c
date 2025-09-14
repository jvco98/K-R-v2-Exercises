#include <stdio.h>

/* 
	Exercise 1-22: Write a program to "fold" long input lines into two or more
	shorter lines after the last non-blank character that occurs before the n-th
	column of input. Make sure your program does something intelligent with very
	long lines, and if there are no blanks or tabs before the specified columns.
*/
#define MAXINPUT			1000/* Largest acceptable user input */
#define MAXLINE				30	/* Largest acceptable line length */
#define TAB_SZ				5  	
#define RETURN_WHITESPACE	1
#define RETURN_POS      	0
#define CURR_TAB_SZ(X)	(TAB_SZ - (X % TAB_SZ))	/* Amount of blank spaces until the next tab index */

int getline(char raw[]);
void foldLine(char line[], int lineLen);
int WORD_WHITESPACE_DATA(char raw[], int whitespaceIndex);
int WORD_END_POS(char raw[], int pos);
int WORD_START_POS(char raw[], int pos);

int main()
{
   	char line[MAXINPUT], folded[MAXINPUT];
   	int rawsize, raw_pos, _word_start, _word_end;

   	while((rawsize = getline(line)) > 0)
		if (rawsize <= MAXINPUT)
   			foldLine(line, rawsize);
		else
			printf("input too long\n");

   	printf("%s", line);

   	return 0;
}

void foldLine(char input[], int lineLen)
{
	int pos = 0;								/* Current position in input[] array */
	// i think we should make pos point to the first character in the current word
	int current_line_count = 0; 				/* Current position in line */
	int wordEnd = 0;							/* Current word end pos */
	int wordStart = WORD_START_POS(input, pos);	/* Current word start pos */

	while (pos < lineLen)
	{	
		// deal with word
		wordEnd = WORD_END_POS(input, pos);
		if ( current_line_count + (wordEnd-pos) >= MAXLINE )
		{
			if (pos == 0)
			{
				printf("entry too long?\n");
				break;
			}
			else
			{
				if (input[pos-1] == ' ')
					input[pos-1] = '\n';
				if (input[pos-1] == '\t')
					printf("tab found... what to do\n");

				current_line_count = (wordEnd - pos) ;
				pos += (wordEnd - pos);
			}
		}
		else
		{
			current_line_count += (wordEnd - pos);
			pos += (wordEnd - pos);
		}
		// deal with spaces, tabs, or newl's in between words
		// in order to get to the start of next word
		
		pos++;	// increment position to move between words
		current_line_count++;

		// if end reached, return
		if (input[pos] == '\n' || input[pos] == '\0')
			break;
		
		int to_add = WORD_WHITESPACE_DATA(input, pos);
		if (to_add + current_line_count >= lineLen)
		{
			printf("spaces causing overflow\n");
		}
		else 
			for (int i = 0; i < to_add; i++)
			{
				input[pos++] = ' ';
				current_line_count++;
			}
	}
	// now that pos >= linelen, we're done. print the folded arr
	printf("%s\n", input);
}

int getline(char raw[]) 
{
	int c, i;
	for (i = 0; ((c = getchar()) != EOF) && (c != '\n'); ++i)
		raw[i] = c;
	if ((c == '\n') && (i != 0))
	{
		raw[i] = c;
		i++;
	}

	raw[i] = '\0';

	return i;
}

/* Returns data pertaining to currently seen word: Index of words last
character */
int WORD_END_POS(char raw[], int pos)
{
	int spaces;
    while (raw[pos] != ' ' && raw[pos] != '\t' && raw[pos] != '\n' && raw[pos] != '\0')
        pos++;

   return --pos;
}

int WORD_WHITESPACE_DATA(char raw[], int whitespaceIndex)
{
	int spaces = 0;
	while(raw[whitespaceIndex] == ' ' || raw[whitespaceIndex] == '\t')
    {
    	if (raw[whitespaceIndex] == ' ')
    	{
    		//printf("last letter seen:%c\n", raw[whitespaceIndex-1]);
    		spaces++;
    		whitespaceIndex++;
    	}
    	else if(raw[whitespaceIndex] == '\t')
    	{
    		printf("spaces before tab:%d\n", spaces);
    		spaces += CURR_TAB_SZ(whitespaceIndex);
    		printf("current space's tab size:%d\n", spaces);
    		whitespaceIndex++;
    	}
    }

    return spaces;
}

int WORD_START_POS(char raw[], int pos)
{
	if (pos == 0)
		return 0;
	else if (raw[pos-1] == ' ' || raw[pos-1] == '\n' || raw[pos-1] == 't')
		if (raw[pos] != ' ' || raw[pos] != '\t' || raw[pos] != '\n' || raw[pos] != '\0')
			return pos;
}