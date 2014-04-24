
/*
 * replace \t	\b	\\ with \\t \\b \\\\ to visible
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int	c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') printf("\\t");
		else if (c == '\\') printf("\\\\");
		else if (c == '\b') printf("\\b");
		else	putchar(c);
	}
	exit(0);
}
