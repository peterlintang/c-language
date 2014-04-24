
/*
 * copy input to output, and replace sequence blanks with only one
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH	180

int main(int argc, char *argv[])
{
	int		c;
	int		flag = 0;

	while ((c = getchar()) != -1) {
		if ((c == ' ') && flag)
			continue;
		else if (c == ' ')
			flag = 1;
		else
			flag = 0;
		putchar(c);
	}
	exit(0);
}
