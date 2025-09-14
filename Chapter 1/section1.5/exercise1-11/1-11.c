/* 
	Exercise 1-11: How would you test the word count program? What kinds of intput
	are most likely to uncover bugs if there are any?
*/
#include <stdio.h>

#define IN 1	/* inside a word */
#define OUT 0	/* outside a word */

/* count lines, words, and characters in input */
int main(void) 
{
	int c, nl, nw, nc, state;
	
	state = OUT;
	nl = nw = nc = 0;

	while((c = getchar()) != EOF) {
		++nc;
		if (c == '\n') {
			++nl;
		}
		if (c == ' ' || c == '\n' || c == '\t') {	
			state = OUT;
		}
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("nl: %d, nw: %d, nc: %d\n", nl, nw, nc);
	
	/* 
		This program can be tested with 3 kinds of inputs. 
		The first set of inputs would be perfectly acceptable, testing for 
		baseline funcctionality.These are valid inputs.
		The second set of inputs would be continuous blank spaces along with 'n',
		'\n', t, 't', or a blank file to observe how the program handles data that
		it is expecting. These are boundary condition inputs. 
		The final set of inputs would be a file which is unclosed, and does not 
		have an EOF. This would be aninvalud input.
	*/
	
}