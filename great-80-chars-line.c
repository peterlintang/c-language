
/*
 * print lines which chars greater then 80
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH	1024
#define	MIN_CHARS	80

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
	int		min_chars = MIN_CHARS;
	int		length = MAXLENGTH;
	char	line[MAXLENGTH];

	while (getline(line, &length) != -1) {
		if (length > min_chars) {
			printf("%s", line);
		}
		length = MAXLENGTH;
	}

	exit(0);
}
