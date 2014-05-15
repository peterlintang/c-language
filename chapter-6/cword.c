
/*
 * count input words frequency
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for strdup

struct tnode {
	char *word;
	int  count;
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
			fprintf(stdout, "%s: %d\n", root->word, root->count);
			print_tree(&root->right);
			free(root->word);
			free(root);
			*rootp = NULL;
		}
	}
}

struct tnode *addtree(struct tnode *root, char *name)
{
	int cond;

	if (!name) {
		fprintf(stderr, "error: argument name :%p is null\n", name);
		return NULL;
	}
	if (!root && (root = calloc(1, sizeof(*root)))) {
		root->word = strdup(name);
		root->count = 1;
		root->left = NULL;
		root->right = NULL;
		return root;
	} 
	if ((cond = strcmp(root->word, name)) == 0) {
		root->count++;
	} else if (cond < 0) {
		root->right = addtree(root->right, name);
	} else if (cond > 0) {
		root->left = addtree(root->left, name);
	}
	return root;
}

int main(int argc, char *argv[])
{
	char word[100];
	struct tnode *root = NULL;

	/*
	 * use getword-2.c 's getword routine
	 */
	while (getword(word, 100) != EOF) {
		if (isalpha(word[0]))
			root = addtree(root, word);
	}
	print_tree(&root);

	exit(0);
}

