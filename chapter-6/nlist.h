
/*
 *	implement a hash table list
 */
#ifndef MY_NLIST_H
#define MY_NLIST_H

struct nlist;


void nlist_init(void);

char *nlist_name(struct nlist *node);

char *nlist_defn(struct nlist *node);

struct nlist *nlist_lookup(char *name);

struct nlist *nlist_install(char *name, char *defn);

int nlist_uninstall(char *name);

void nlist_print(void);

#endif
