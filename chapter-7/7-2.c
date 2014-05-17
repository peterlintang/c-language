
/*
 * input to output and separate long line to short lines
 * for unprintable chars , print hex or ..
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLEN	80
#define OCTLEN	6

static int inc(int pos, int len)
{
	if (pos + len < MAXLEN)
		return pos + len;
	else {
		putchar('\n');
		return 0;
	}
}

int main(int argc, char *argv[])
{
	int pos;
	int c;

	while ((c = getchar()) != EOF) {
		if (iscntrl(c) || c == ' ') {
			pos = inc(pos, OCTLEN);
			printf("\\%03o", c);
			if (c == '\n') {
				pos = 0;
				putchar(c);
			}
		} else {
			pos = inc(pos, 1);
			putchar(c);
		}
	}

	exit(0);
}
