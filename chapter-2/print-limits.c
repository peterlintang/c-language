
/*
 * print the max and min values of unsigned signed char short int 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("signed char min = %d\n", -(char)((unsigned char)~0 >> 1));
	printf("signed char max = %d\n", (char)((unsigned char)~0 >> 1));
	printf("signed short min = %d\n", -(short)((unsigned short)~0 >> 1));
	printf("signed short max = %d\n", (short)((unsigned short)~0 >> 1));

	printf("unsigned char max = %u\n", (unsigned char)~0);
	printf("unsigned short max = %u\n", (unsigned short)~0);
	printf("unsigned int max = %u\n", (unsigned int)~0);
	printf("unsigned long int max = %lu\n", (unsigned long)~0);
	exit(0);
}
