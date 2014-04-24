
/*
 * count blanks tabs lines from input
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int	blank;
	int	tab;
	int	line;
	int	c;

	blank 	= 0;
	tab		= 0;
	line	= 0;

	while ((c = getchar()) != EOF) {
		switch (c) {
		case ' ':	blank++; 
			break;
		case '\t':	tab++; 	
			break;
		case '\n':	line++;
			break;
		default: 
			break;
		}
	}

	fprintf(stdout, "\nblank: %d, tab: %d, line: %d\n", blank, tab, line);
	exit(0);
}
