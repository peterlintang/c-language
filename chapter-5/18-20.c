
/*
 * exercise 18 - 20 code or not depend on u
 * seems not working
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define getch() getchar()
#define ungetch(c) ungetc(c, stdin)

#define MAXTOKEN 	100

enum { NAME, PARENS, BRACKETS };

int  tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void dcl(void);
void dirdcl(void);

int gettoken(void)
{
	int c;
	char *p = token;
	
	while ((c = getch()) == ' ' || (c == '\t'))
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalnum(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0) {
		strcat(out, " pointer to");
	}
}

void dirdcl(void)
{
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			fprintf(stderr, "error: missing )\n");
	} else if (tokentype == NAME) {
		strcpy(name, token);
	} else {
		fprintf(stderr, "error: expected name or (dcl)\n");
	}

	while ((type == gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returnning");
		else {
			strcat(out, " array");
			strcat(out, " token");
			strcat(out, " of");
		}
}



int main(int argc, char *argv[])
{
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n')
			fprintf(stderr, "syntax error\n");
		fprintf(stdout, "%s: %s %s\n", name, out, datatype);
	}
	exit(0);
}
