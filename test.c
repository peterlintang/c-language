
#include <stdio.h>


enum MON { FRE, MAY };

#define TEST_ID	8251342990823333ULL

static unsigned int temp = 10;
int test(char array[][4])
{
	char	c = 'ab';
	int i, j;
	float fa = 1.3e-2;	/* 1.3 * 10^2 */
	static int temp = 0;
	printf("fa: %f, temp: %d\n", fa, \
			temp);
	printf("c: %c\n", c);
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			printf("array[%d][%d]: %p\n", i, j, &array[i][j]);
	return 0;
}

int test2(char array[][4])
{
//	struct point a;
	return 0;
}

int main(int argc, char *argv[])
{
	struct a_ {
		int i;
		int	c:3;
		char	str[0];
	};
	struct b_ {
		struct a;
		int i;
	};
	int	(i) = 0;
	unsigned char row[250] = "hello world";
	unsigned char *p = &row[2];
	char	array[4][4];
	extern unsigned int temp;	// wrong
//	int temp;
	char	tmp = TEST_ID;
	int (*func)(char array[][4]);
	int (*funcarray[2])(char array[][4]);
	struct point {
		float x;
		float y;
	};
	printf("%c\n", p[-1]);
	printf("%d\n", tmp);
	printf("tmp: %u\n", temp + 6553689999999);
	printf("tmp: %d\n", temp + 6553689999999);
	func = &test;
	func(array);
	printf("\n\nhello nice good\n\n");
	func = test;
	func(array);
	funcarray[0] = test;
	funcarray[1] = test2;
	printf("hello\n\n");
	funcarray[0](array);
	funcarray[1](array);
	printf("hello\n\n");
//	printf("i: %d\n", ++i++);	// error, since i++ is not a left value

	printf("%p, %c\n", row+2, *(row + 2));
	printf("%p\n", (void *)(*((unsigned int*)(row+2))));
	printf("%p\n", (((unsigned int*)(row+2))));
	printf("%d\n", (*((unsigned int*)(row+2))));
	(*func)(array);
	do {
		if (i == 2) continue;
		printf("i: %d\n", i);
	} while (i++ < 4);
	test(array);
	printf("0x%0x 0x%0x\n", 0, ~0);
	printf("%d\n", 0200);
	exit(0);
}
