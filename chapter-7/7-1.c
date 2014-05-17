
/*
 * convert lower char to upper char 
 * or the opposite according to the argv
 * in command line
 */

#include <stdio.h>
#include <stdlib.h>

#define LOWER_TO_UPPER	1
#define UPPER_TO_LOWER	0

void usage(char *s)
{
	fprintf(stdout, "usage: %s [ v | V ]\n", s);
	exit(-1);
}

int main(int argc, char *argv[])
{
	int c;
	int opt;
	int v = LOWER_TO_UPPER;

	while ((opt = getopt(argc, argv, "vV")) != -1) {
		switch (opt) {
		case 'v':
			v = UPPER_TO_LOWER;
			break;
		case 'V':
			v = LOWER_TO_UPPER;
			break;
		default:
			usage(argv[0]);
			break;
		}
	}

	if (v == UPPER_TO_LOWER) {
		while ((c = getchar()) != EOF) {
			putchar(tolower(c));
		}
	} else if (v == LOWER_TO_UPPER) {
		while ((c = getchar()) != EOF) {
			putchar(toupper(c));
		}
	} else {
		usage(argv[0]);
	}

	exit(0);
}
