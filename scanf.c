
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char	tmp[50];
	int		num;
	sscanf("hello 2 world 128", "%s %*d %*s %d", tmp, &num);
	printf("%s\n", tmp);
	printf("%d\n", num);
	return 0;
}
