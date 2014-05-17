
/*
 * get a word from stdin, 
 * add support for '_' '#' and comments
 */
#include <stdio.h>

#define getch() getchar()
#define ungetch(c) ungetc(c, stdin)

int comment(void)
{
	int c;

	while ((c = getch()) != EOF) {
		if (c == '*') {
			c = getch();
			if (c == '/')
				break;
			else 
				ungetch(c);
		}
	}
	return c;
}

int getword(char *s, int lim)
{
	int c;
	int d;

	/*
	while (isspace(c = getch()))
		;
	*/

	c = getch();
	/*
	if (c == EOF) {
		*s = '\0';
		return c;
	}
	*/

	if (isalpha(c) || c == '_' || c == '#') {
		*s++ = c;
		for (; --lim > 0; ) {
			if (!isalnum(c = getch()) && c != '_') {
				ungetch(c);
				break;
			}
			*s++ = c;
		}
	} else if (c == '"') {
		*s++ = c;
		for (; --lim > 0; s++) {
			*s = getch();
			if (*s == '\\') {
				*++s = getch();
			} else if (*s == c) {
				s++;
				break;
			} else if (*s == EOF) {
				break;
			}
		}
	}  else if (c == '/'){
		*s++ = c;
		d = getch();
		if (d == '*')
			c = comment();
		else
			ungetch(d);
	} else {
		*s++ = c;
		*s = '\0';
		return c;
	}
	*s = '\0';
	return s[0];
}

/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char word[101];
	while (getword(word, 100) != EOF)
		fprintf(stdout, "word: %s\n", word);
	exit(0);
}
*/
