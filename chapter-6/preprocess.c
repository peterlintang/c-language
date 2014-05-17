
/*
 *	c code preprocess
 *	very simple
 *	not very good, in face it have some bugs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nlist.h"

#define LEN	100

int get_macro(char *s)
{
	int c;

	while (isspace(c = getchar()))
		;
	if (isalnum(c)) {
		*s++ = c;
		for (; c = getchar(); ) {
			if (!isalnum(c)) {
				ungetc(c, stdin);
				*s = '\0';
				return c;
			}
			*s++ = c;
		}
	} else 
		*s++ = c;
	*s = '\0';
	return c;
}

int main(int argc, char *argv[])
{
	int 	c;
	char	word[100];
	char	defn[100];
	struct nlist *node = NULL;

	int	test;
	test = LEN;

	nlist_init();
	/*
	 * use getword-3.c getword routine
	 */
	while ((c = getword(word, 100)) != -1) {
		if (isalpha(word[0])) {
			if ((node = nlist_lookup(word)) 
					&& (strcmp(nlist_name(node), word) == 0)) {
				fprintf(stdout, "%s", nlist_defn(node));
			} else {
				fprintf(stdout, "%s", word);
			}
		} else if (strcmp(word, "#include") == 0) {
			fprintf(stdout, "%s", word);
		} else if (strcmp(word, "#define") == 0) {
			get_macro(word);
			get_macro(defn);
//			fprintf(stdout, "word: %s, defn: %s\n", word, defn);
			nlist_install(word, defn);
		} else if (word[0] == '"') {
			fprintf(stdout, "%s", word);
		}else {
			fprintf(stdout, "%c", c);
		}
	}
	exit(0);
}
