
/*
 * relace sequence blanks with lest tab and blanks
 */
#include <stdio.h>
#include <stdlib.h>

#define IN_BLANKS	1
#define OUT_BLANKS	0
#define BLANKS		4

void replace(int old_pos, int pos, int c)
{
	int	spaces;

	while (old_pos < pos) {
		spaces = BLANKS - (old_pos - 1) % BLANKS;
		if (old_pos + spaces <= pos)
			putchar('\t');
		else
			break;
		old_pos += spaces;
	}

	if (c != '\t') {
		while (old_pos < pos) {
			putchar(' ');
			old_pos++;
		}
	}
}

int main(int argc, char *argv[])
{
	int		c;
	int		old_pos;
	int		pos = 1;
	int		status = OUT_BLANKS;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (status == OUT_BLANKS) {
				status = IN_BLANKS;
				old_pos = pos;
			}
			pos++;
		} else {
			if (status == IN_BLANKS) {
				status = OUT_BLANKS;
				replace(old_pos, pos, c);
				if (c == '\n')
					pos = 1;
				else if (c == '\t')
					pos += (BLANKS - (pos - 1) % BLANKS - 1);
				else
					pos++;
			}
			putchar(c);
		}
	}

	exit(0);
}
