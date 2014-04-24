
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	void	*cmd = NULL;
	unsigned char	cdb[] = "hello world";

	cmd = (void *)(*((int *)(cdb + 4)));
	printf("cdb: %s\n", cdb);
	printf("cmd: %p, cdb: %p, cdb+4: %p\n", cmd, cdb, cdb + 4);
	printf("(int *)(cdb + 4): %p\n", (int *)(cdb + 4));
	printf("(*((int *)(cdb + 4))): %c\n", (*((int *)(cdb + 4))));

	exit(0);
}
