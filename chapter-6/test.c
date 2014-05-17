



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nlist.h"



void error(char *s)
{
	fprintf(stderr, "%s\n");
	exit(-1);
}

int do_macro(void)
{
	int c;
	char s[100];
	char d[100];

	while (isspace(c = getchar()))
		;
	ungetc(c, stdin);
	if ((c = getword(s, 100)) == -1) {
		error("faile to get macro name");
	}

	if (strcmp(s, "define") == 0) {
		while (isspace(c = getchar()))
			;
		ungetc(c, stdin);
		if ((c = getword(s, 100)) == -1) {
			error("faile to get macro name");
		}

		while (isspace(c = getchar()))
			;
		ungetc(c, stdin);
		if ((c = getword(d, 100)) == -1) {
			error("faile to get macro define");
		}
		nlist_install(s, d);
	} else if (strcmp(s, "undef") == 0) {
		while (isspace(c = getchar()))
			;
		ungetc(c, stdin);
		if ((c = getword(s, 100)) == -1) {
			error("faile to get macro name");
		}
		nlist_uninstall(s);
	} else if (strcmp(s, "include") == 0) {
		fprintf(stdout, "%c", '#');
		fprintf(stdout, "%s", s);
	} else {
		fprintf(stderr, "unknow type: %s\n", s);
	}

	return c;
}

int main(int argc, char *argv[])
{
	int 	c;
	char	word[100];
	char	defn[100];
	struct nlist *node = NULL;

	int	test;
	test = 9;

	nlist_init();
	

	while ((c = getword(word, 100)) != -1) {
		if (isalpha(word[0])) {
			if ((node = nlist_lookup(word)) 
					&& (strcmp(nlist_name(node), word) == 0)) {
				fprintf(stdout, "%s", nlist_defn(node));
			} else {
				fprintf(stdout, "%s", word);
			}
		} else if (c == '#') {
			do_macro();
		}else if (word[0] == '"' || word[0] == '\'') {
			fprintf(stdout, "%s", word);
		} else {
			fprintf(stdout, "%c", c);
		}
	}
	nlist_destroy();
	exit(0);
}
