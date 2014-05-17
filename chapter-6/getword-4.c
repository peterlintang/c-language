
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

	c = getch();

	if (isalpha(c) || c == '_') {
		*s++ = c;
		for (; --lim > 0; ) {
			if (!isalnum(c = getch()) && c != '_') {
				ungetch(c);
				break;
			}
			*s++ = c;
		}
	} else if (c == '"' || c == '\'') {
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
	} else if (c == '/') {
		*s++ = c;
		d = getch();
		if (d == '*') {
			c = comment();
			*s = '\0';
			return '\n';
		} else
			ungetch(d);
	} else {
		*s++ = c;
		*s = '\0';
		return c;
	}
	*s = '\0';
	return s[0];
}

