
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

int main(int argc, char *argv[])
{
	int		i;
	int		length = MAXLENGTH;
	char	line[MAXLENGTH];

	while (getline(line, &length) != -1) {
		i = length - 1;
		if (line[i] == '\n')
			i--;
		while (i >= 0) {
			if ((line[i] == '\t') || (line[i] == ' '))
				i--;
			else
				break;
		}
		if (i >= 0) {
			line[i++] == '\n';
			line[i] == '\0';
			printf("%s", line);
		}

		length = MAXLENGTH;
	}

	exit(0);
}
