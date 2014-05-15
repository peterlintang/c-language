
/*
 * relace tab with correct num of blanks
 */
#include <stdio.h>
#include <stdlib.h>

#define BLANKS		4


int main(int argc, char *argv[])
{
	int		c;
	int		spaces;
	int		pos = 1;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			spaces = BLANKS - (pos - 1) % BLANKS;
			while (spaces-- > 0) {
				putchar(' ');
				pos++;
			}
		} else {
			putchar(c);
			if (c == '\n')
				pos = 1;
			else
				pos++;
		}
	}

	exit(0);
}
