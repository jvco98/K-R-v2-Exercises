#include <stdio.h>

/* 
	Exercise 1-22: Write a program to "fold" long input lines into two or more
	shorter lines after the last non-blank character that occurs before the n-th
	column of input. Make sure your program does something intelligent with very
	long lines, and if there are no blanks or tabs before the specified columns.
*/
#define MAXINPUT			1060/* Largest acceptable user input */
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

	/* you may want to convert '\t' into spaces... When a \t will cause 
		a line to overflow, there isn't a great way to fold the tab space...
		if you make the tab into individual blank spaces, you can cut it off
		immediately upon overflowing, and even carry on the remmaining blank
		spaces into the next line. How should this be handled?
	*/


void foldLine(char line[], int lineLen)
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


