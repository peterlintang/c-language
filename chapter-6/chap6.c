
/*
 * get a word from stdin, 
 */
#include <stdio.h>

#define getch() getchar()
#define ungetch(c) ungetc(c, stdin)

int getword(char *s, int lim)
{
	int c;

	while (isspace(c = getch()))
		;

	/*
	if (c == EOF) {
		*s = '\0';
		return c;
	}
	*/

	if (isalpha(c)) {
		*s++ = c;
		for (; --lim > 0; ) {
			if (!isalnum(c = getch())) {
				ungetch(c);
				break;
			}
			*s++ = c;
		}
	} else {
		*s = '\0';
		return c;
	}
	*s = '\0';
	return s[0];
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char word[101];
	while (getword(word, 100) != EOF)
		fprintf(stdout, "word: %s\n", word);
	exit(0);
}
