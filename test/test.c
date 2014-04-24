
#include <stdio.h>

#define TEST_ID	8251342990823333ULL

/*
int [4]hello(int id) 
{
	int a[4];
	return a;
}
*/

int test(char array[][4])
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			printf("array[%d][%d]: %p\n", i, j, &array[i][j]);
	return 0;
}
int main(int argc, char *argv[])
{
//	enum KEY { NO, YES };
	enum months { NO, YES };
	int	i = 0;
	unsigned char row[250] = "hello world";
	char	array[4][4];
	char	tmp = TEST_ID;
	union u_tag {
		int val;
		char *str;
	} u;
	u.str = "hello";
	printf("%d\n", tmp);

	printf("%p, %c\n", row+2, *(row + 2));
	printf("%p\n", (void *)(*((unsigned int*)(row+2))));
	printf("%p\n", (((unsigned int*)(row+2))));
	printf("%d\n", (*((unsigned int*)(row+2))));
	do {
		if (i == 2) continue;
		printf("i: %d\n", i);
	} while (i++ < 4);
	test(array);
	exit(0);
}
