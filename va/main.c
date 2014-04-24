
#include<stdio.h>

#include "print.h"

int main(int argc, char *argv[])
{
	myprintf("%s %c, %x, %o\n", "hello world", 'c', 156, 18);
	return 0;
}
