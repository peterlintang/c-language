
/*
 * print stdin to stdout, one word per line
 */
#include <stdio.h>
#include <stdlib.h>

#define IN_WORD		0
#define OUT_WORD	1

int main(int argc, char *argv[])
{
	int	state = OUT_WORD;
	int	c;

	while ((c = getchar()) != EOF) {
		if (state == IN_WORD) {
			if ((c == '\n') || (c == ' ') || (c == '\t')) {
				putchar('\n');
				state = OUT_WORD;
			} else {
				putchar(c);
			}
		} else if (state == OUT_WORD) {
			if ((c == '\n') || (c == ' ') || (c == '\t')) {
			} else {
				state = IN_WORD;
				putchar(c);
			}
		}
	}

	/*	this is the implementation in c-l books
	while ((c = getchar()) != EOF) {
		if ((c == '\n') || (c == ' ') || (c == '\t')) {
			if (state == IN_WORD) {
				putchar('\n');
				state = OUT_WORD;
			}
		} else if (state == OUT_WORD) {
			state = IN_WORD;
			putchar(c);
		} else {
			putchar(c);
		}
	}
	*/

	exit(0);
}
