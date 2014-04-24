
/*
 * print as many text as we can, and print the longest line
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH	1024

int getline(char *str, int *plen)
{
	static int endoffile = 0;
	int		c;
	int		total = 0;

	if (endoffile == 1) return -1;

	while (((c = getchar()) != EOF) && (total++ < *plen)) {
		if ((*str++ = c) == '\n')
			break;
	}
	*str = '\0';
	if (c == EOF) endoffile = 1;
	*plen = total;

	return total;
}

int copyline(char *dst, char *src)
{
	for (; (*dst++ = *src++) != '\0'; )
		;
	return 0;
}

int main(int argc, char *argv[])
{
	int		length = MAXLENGTH;
	int		lenmax    = 0;
	char	line[MAXLENGTH];
	char	longest[MAXLENGTH];

	while (getline(line, &length) != -1) {
		printf("len: %d, line: %s", length, line);
		if (length > lenmax) {
			copyline(longest, line);
			lenmax = length;
		}
		length = MAXLENGTH;
	}

	putchar('\n');
	if (lenmax > 0) {
		printf("longest len: %d, line: %s\n", lenmax, longest);
	}

	exit(0);
}
