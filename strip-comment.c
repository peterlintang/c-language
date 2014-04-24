
/*
 * strip the comments of c code
 * "ls  lsdf"
 */
#include <stdio.h>
#include <stdlib.h>

#define OUT_QUOTE	0
#define	IN_QUOTE	1
#define IN_COMMENT	2
#define OUT_COMMENT	3
#define ONE_LINE	0x10

int main(int argc, char *argv[])
{
	int	prev_c;
	int	c;
	int status = OUT_QUOTE;
	int	comment = OUT_COMMENT;
	char	*p = "hello world /*sldfs*/ hello baby";

	while ((c = getchar()) != EOF) {
		if (status == IN_QUOTE) {
			if (c == '"') status = OUT_QUOTE;
			putchar(c);
			continue;
		} else if (status == OUT_QUOTE) {
			if (comment == OUT_COMMENT) {
				if (c == '"') {
					status = IN_QUOTE;
					putchar(c);
					continue;
				}
			}
		}
		/*
		 * TODO we for now just dont consider the quote status
		 */
		if (comment == IN_COMMENT) {
			prev_c = c;
			if ((comment & ONE_LINE) == ONE_LINE) {
				if (prev_c == '\n')
					comment = OUT_COMMENT;
				continue;
			}
			if ((prev_c == '*') && ((c = getchar()) == '/'))
				comment = OUT_COMMENT;
			if ((prev_c == '/') && ((c = getchar()) == '*')) {
				printf("not support nest comments\n");
				exit(1);
			}
		} else if (comment == OUT_COMMENT) {
			prev_c = c;
			if (prev_c == '/') {
				if ((c = getchar()) == '*') {
//				if (((c = getchar()) == '*') || (c == '/')) {
					comment = IN_COMMENT;
				} else if (c == '/') {
					comment = IN_COMMENT | ONE_LINE;
				} else {
					putchar(prev_c);
					putchar(c);
				}
			} else {
				putchar(prev_c);
			}
		}
	}

	exit(0);
}

