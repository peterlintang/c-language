
/*
 * count input words frequency
 * and record the line nums of the word appearence
 * 6-3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for strdup

struct tnode {
	char *word;
	int  count;	// remember the elements in array
	int	 *array;
	struct tnode *left;
	struct tnode *right;
};

void print_tree(struct tnode **rootp)
{
	struct tnode *root = NULL;
	if (rootp) {
		root = *rootp;
		if (root) {
			int i;
			print_tree(&root->left);
			fprintf(stdout, "%s: ", root->word);
			for (i = 0; i < root->count; i++)
				fprintf(stdout, "%d ", root->array[i]);
			fprintf(stdout, "\n");
			print_tree(&root->right);
			free(root->word);
			free(root->array);
			free(root);
			*rootp = NULL;
		}
	}
}

struct tnode *addtree(struct tnode *root, char *name, int n)
{
	int cond;

	if (!name) {
		fprintf(stderr, "error: argument name :%p is null\n", name);
		return NULL;
	}
	if (!root && (root = calloc(1, sizeof(*root)))) {
		root->word = strdup(name);
		root->array = calloc(1, sizeof(int));
		root->count = 1;
		root->array[0] = n;
		root->left = NULL;
		root->right = NULL;
		return root;
	} 
	if ((cond = strcmp(root->word, name)) == 0) {
		int i;
		int found = 0;
		for (i = 0; i < root->count; i++)
			if (root->array[i] == n) {
				found = 1;
				break;
			}
		if (!found) {
			root->count++;
			root->array = realloc(root->array, sizeof(int) * root->count);
			root->array[root->count - 1] = n;
		}
	} else if (cond < 0) {
		root->right = addtree(root->right, name, n);
	} else if (cond > 0) {
		root->left = addtree(root->left, name, n);
	}
	return root;
}

int getword(char *s, int lim);

int main(int argc, char *argv[])
{
	char word[100];
	int		linenum = 1;
	int	c;
	struct tnode *root = NULL;

	while ((c = getword(word, 100)) != EOF) {
		if (isalpha(word[0]))
			root = addtree(root, word, linenum);
		else if (word[0] == '\n')
			linenum++;
	}
	print_tree(&root);

	exit(0);
}


/*
 * get a word from stdin, 
 * add support for '_' '#' and comments
 * modify for return \n for this program
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

	while ((c = getch()) == ' ' || c == '\t'
			|| c == '\f' || c == '\v' || c == '\r')
		;

	if (isalpha(c) || c == '_' || c == '#') {
		*s++ = c;
		for (; --lim > 0; ) {
			if (!isalnum(c = getch()) && c != '_') {
				ungetch(c);
				break;
			}
			*s++ = c;
		}
	} else if (c == '\'' || c == '"') {
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
	} else if (c == '/'){
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

