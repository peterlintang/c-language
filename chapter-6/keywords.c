
/*
 * count the key words of c code
 * and print them to stdout
 */

#include <stdio.h>
#include <stdlib.h>

struct key_word {
	char *name;
	int	 count;
};

static struct key_word keywords[] = {
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0},
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	{ "do", 0 },
	{ "double", 0 },
	{ "else", 0 },
	{ "enum", 0 },
	{ "extern", 0 },
	{ "float", 0 },
	{ "for", 0 },
	{ "goto", 0 },
	{ "if", 0 },
	{ "int", 0 },
	{ "long", 0 },
	{ "register", 0 },
	{ "return", 0 },
	{ "short", 0 },
	{ "signed", 0 },
	{ "sizeof", 0 },
	{ "static", 0 },
	{ "struct", 0 },
	{ "switch", 0 },
	{ "typedef", 0 },
	{ "union", 0 },
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 },
	{ NULL, 0 },
};

void keywords_print(struct key_word *key)
{
	if (!key) return;

	for (; key->name != NULL; key++)
		fprintf(stdout, "key word: %s, count: %d\n", 
				key->name, key->count);
}

struct key_word *search_key(struct key_word *words, char *name)
{
	struct key_word *key = NULL;

	if (!words || !name) 
		return NULL;
	for ( key = words; key->name != NULL; key++) {
		if (strcmp(key->name, name)) 
			continue;
		return key;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	char word[100];
	struct key_word *key = NULL;

	/*
	 * use getword-2.c 's getword routine
	 */
	while (getword(word, 100) != EOF) {
		if (isalpha(word[0])) {
			key = search_key(keywords, word);
			if (key) 
				key->count++;
		}
	}
	keywords_print(keywords);
	exit(0);
}
