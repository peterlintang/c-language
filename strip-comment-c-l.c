
/*
 * strip comments of c code
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * code from c-l book
 */
int in_comment(void)
{
	int c, d;

	c = getchar();
	d = getchar();
	while ((c != '*') || (d != '/')) {
		c = d;
		d = getchar();
	}

}

int echo_quot(int c)
{
	int d;

	putchar(c);
	while ((d = getchar()) != c) {
		putchar(d);
		if (d == '\\')
			putchar(getchar());
	}
	putchar(d);
	return 0;
}

int rcomment(int c)
{
	int d;

	if (c == '/') {
		if ((d = getchar()) == '*') {
			in_comment();
		} else if (d == '/') {
			putchar(c);
			rcomment(d);
		} else {
			putchar(c);
			putchar(d);
		}
	} else if ((c == '\'') || (c == '"')) {
		echo_quot(c);
	} else {
		putchar(c);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int c;

	while ((c = getchar()) != EOF) {
		rcomment(c);
	}
	exit(0);
}
