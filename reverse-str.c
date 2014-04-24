
/*
 * print as many text as we can, and print the longest line
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH	1024

/*
 * get a line from stdin
 * return value	: num of chars getted
 * 				  -1 error ( end of file )
 */
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

int reverse(char *str)
{
	int low;
	int high;
	char	tmp;

	if (!str)
		return -1;

	low = 0;
	high = 0;
	while (str[high] != '\0')
		high++;
	--high;
	if (str[high] == '\n')
		--high;
	while (low < high) {
		tmp = str[low];
		str[low] = str[high];
		str[high] = tmp;
		low++;
		high--;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int		length = MAXLENGTH;
	int		lenmax    = 0;
	char	line[MAXLENGTH];
	char	longest[MAXLENGTH];

	while (getline(line, &length) != -1) {
		reverse(line);
		printf("%s", line);
		length = MAXLENGTH;
	}

	exit(0);
}
