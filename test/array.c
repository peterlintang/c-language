
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i, j, k;
	int x3d[2][3][4];

	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 4; k++)
				printf("x3d[%d][%d][%d]: %p\n", i, j, k, &x3d[i][j][k]);
	exit(0);
}
