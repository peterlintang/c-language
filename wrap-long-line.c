
/*
 * wrap long line tnto several short lines
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH		1024
#define COL_WRAP_POS	24

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

int print_wrap_line(char *line)
{
	printf("%s", line);
	putchar('\n');
}

int wrap_long_line(char *line, int length)
{
	int	 i = 0;
	int  n = 0;
	char wrap_line[COL_WRAP_POS + 1];

	/*
	 * we dont consider so much about '\t' chars
	 * just do the simplest thing
	 */
	while (length > COL_WRAP_POS) {
		for (i = 0; i < COL_WRAP_POS; i++) {
			wrap_line[i] = line[n * COL_WRAP_POS + i];
		}
		wrap_line[i] = '\0';
		n++;
		length -= COL_WRAP_POS;
		print_wrap_line(wrap_line);
	}

	if (length > 0) {
		printf("%s", &line[n * COL_WRAP_POS]);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int		length = MAXLENGTH;
	char	line[MAXLENGTH];

	while (getline(line, &length) != -1) {
		wrap_long_line(line, length);
		length = MAXLENGTH;
	}
	exit(0);
}
