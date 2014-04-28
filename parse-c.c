
/*
 * parse c code for brace brack paren error
 */

#include <stdio.h>
#include <stdlib.h>

int brace, brack, paren;

void in_comment(void);
void in_quote(int c);
void search(int c);

void search(int c)
{
	if (c == '{')
		++brace;
	else if (c == '}')
		--brace;
	else if (c == '[')
		++brack;
	else if (c == ']')
		--brack;
	else if (c == '(')
		++paren;
	else if (c == ')')
		--paren;
}

void in_comment(void)
{
	int c, d;

	c = getchar();
	d = getchar();

	while ((c != '*') || (d != '/')) {
		c = d; 
		d = getchar();
	}
}

void in_quote(int c)
{
	int d;

	while (( d = getchar()) != c) {
		if (d == '\\')
			getchar();
	}
}

int main(int argc, char *argv[])
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '/') {
			if ((c = getchar()) == '*')
				in_comment();
			else
				search(c);
		} else if ((c == '\'') || (c == '\"')) {
			in_quote(c);
		} else {
				search(c);
		}

		if (brace < 0) {
			printf("unbalanced braces\n");
		}
		if (brack < 0) {
			printf("unbalanced brack\n");
		}
		if (paren < 0) {
			printf("unbalanced paren\n");
		}
	}
	if (brace > 0) {
		printf("unbalanced braces\n");
	}
	if (brack > 0) {
		printf("unbalanced brack\n");
	}
	if (paren > 0) {
		printf("unbalanced paren\n");
	}

	exit(0);
}
