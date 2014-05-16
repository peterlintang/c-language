
/*
 * count input words frequency
 * 6-2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for strdup
#include <unistd.h>	// for getopt

#define YES	1
#define NO	0

struct tnode {
	char *word;
	int  match;
	struct tnode *left;
	struct tnode *right;
};

void print_tree(struct tnode **rootp)
{
	struct tnode *root = NULL;
	if (rootp) {
		root = *rootp;
		if (root) {
			print_tree(&root->left);
			if (root->match == YES) {
				fprintf(stdout, "%s\n", root->word);
			}
			print_tree(&root->right);
			free(root->word);
			free(root);
			*rootp = NULL;
		}
	}
}

int compare(struct tnode *p, char *s, int num, int *found)
{
	int i;
	char *s1 = p->word;
	char *s2 = s;
	for (i = 0; *s1 == *s2; s1++, s2++, i++)
		if (*s1 == '\0')
			return 0;
	if (i >= num) {
		p->match = YES;
		*found = YES;
	}
	return *s1 - *s2;
}

struct tnode *addtree(struct tnode *root, 
		int (*cmp)(struct tnode *p, char *s, int num, int *found), 
		int num, char *name, int *found)
{
	int cond;

	if (!name) {
		fprintf(stderr, "error: argument name :%p is null\n", name);
		return NULL;
	}
	if (!root && (root = calloc(1, sizeof(*root)))) {
		root->word = strdup(name);
		root->match = *found;
		root->left = NULL;
		root->right = NULL;
		return root;
	} 
	if ((cond = cmp(root, name, num, found)) == 0) {
		;
	} else if (cond < 0) {
		root->right = addtree(root->right, cmp, num, name, found);
	} else if (cond > 0) {
		root->left = addtree(root->left, cmp, num, name, found);
	}
	return root;
}

void usage(char *prog)
{
	fprintf(stderr, "usage: %s [ -n num ]\n", prog);
	exit(-1);
}

int main(int argc, char *argv[])
{
	char word[100];
	struct tnode *root = NULL;
	int  len = 6;
	int	 found = NO;

	int opt;

	while ((opt = getopt(argc, argv,"n:")) != -1) {
		switch (opt) {
			case 'n':
				len = atoi(optarg);
				break;
			default:
				fprintf(stderr, "unknow opt: %c\n", opt);
				usage(argv[0]);
				break;
		}
	}

	/*
	 * use getword-2.c 's getword routine
	 */
	while (getword(word, 100) != EOF) {
		if (isalpha(word[0]) && (strlen(word) >= len))
			root = addtree(root, compare, len, word, &found);
		found = NO;
	}
	print_tree(&root);

	exit(0);
}

