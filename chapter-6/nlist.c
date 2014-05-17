
/*
 *	implement a hash table list
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXHASH	100

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtable[MAXHASH];

char *nlist_name(struct nlist *node) 
{
	return node ? node->name : NULL;
}

char *nlist_defn(struct nlist *node)
{
	return node ? node->defn : NULL;
}

static inline unsigned int hash(char *s)
{
	unsigned int value = 0;
	for (; *s != '\0'; s++)
		value = *s + 31 * value;
	return value % MAXHASH;
}

void nlist_init(void)
{
	int i;
	for (i = 0; i < MAXHASH; i++)
		hashtable[i] = NULL;
}

void nlist_destroy(void)
{
	int i;
	struct nlist *node = NULL;
	struct nlist *next = NULL;

	for (i = 0; i < MAXHASH; i++) {
		if (!(node = hashtable[i])) 
			continue;
		for (; node; node = next) {
			next = node->next;
			free(node->name);
			free(node->defn);
			free(node);
		}
		hashtable[i] = NULL;
	}
}

struct nlist *nlist_lookup(char *name)
{
	struct nlist *node = NULL;

	for (node = hashtable[hash(name)]; node; node = node->next) {
		if (strcmp(node->name, name) == 0)
			break;
	}
	return node;
}

struct nlist *nlist_install(char *name, char *defn)
{
	struct nlist *node = NULL;

	if (!name || !defn)
		return NULL;

	node = nlist_lookup(name);
	if (node) {	/* found in table, replace defn*/
		free(node->defn);
		node->defn = strdup(defn);	// hope will success
	} else if (node = calloc(1, sizeof(*node))) {
		node->name = strdup(name);
		node->defn = strdup(defn);
		node->next = hashtable[hash(name)];
		hashtable[hash(name)] = node;
	}

	return node;
}

int nlist_uninstall(char *name)
{
	int ret = -1;
	struct nlist *node = NULL;
	struct nlist *prev = NULL;

	if (!name)
		goto out;

	for (node = hashtable[hash(name)]; node; node = node->next) {
		if (strcmp(node->name, name) == 0)
			break;
		prev = node;
	}

	if (!node) {
		ret = -2;	// not found
		goto out;
	}

	if (node == hashtable[hash(name)]) {
		hashtable[hash(name)] = node->next;
	} else {
		prev->next = node->next;
	}
	free(node->name);
	free(node->defn);
	free(node);

out:
	return 0;
}


void nlist_print(void)
{
	int i;
	struct nlist *node = NULL;

	for (i = 0; i < MAXHASH; i++) {
		node = hashtable[i];
//		fprintf(stdout, "element: %d\n", i);
		for (; node; node = node->next)
			fprintf(stdout, "name: %s, define: %s\n", 
					node->name, node->defn);
	}

}

/*
 * test

#define WORD_LEN	100
int main(int argc, char *argv[])
{
	char name[WORD_LEN];
	char defn[WORD_LEN];

	while ((getword(name, WORD_LEN) != -1) 
			&& (getword(defn, WORD_LEN) != -1)) {
		if (isalpha(name[0]) && isalpha(defn[0]))
					nlist_install(name, defn);
	}
	nlist_print();
	nlist_uninstall("nice");
	nlist_print();
	exit(0);
}

 */
