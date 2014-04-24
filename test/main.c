
#include <stdio.h>
#include <stdlib.h>	// for exit
#include <dlfcn.h>	// for dlopen dlerror dlsym dlclose routines

#define Dprint(fmt, args...)	printf(fmt, ##args)
//#define Dprint(fmt, args...)	printf(fmt, args)	// two are ok
int global;

int main(int argc, char *argv[])
{
	float f = 0.4;
	void *handle = NULL;
	char *array[3];
	int (*func)(int , char *[]);
	func = NULL;

	1 ? "hello world" : 2;
	Dprint("%s, %s\n", "hello", "world");
	printf("global: %d\n", global);
	printf("??= ??<\n");	// gcc -o my main.c -ldl -ansi
	printf("%d\n", -111);
	printf("%x\n", -111);
	printf("%o\n", -111);
	if (f) {
		printf("flaot\n");
	}
	/*
	for (; f; ) {
		printf("for \n");
	}
	*/

	switch (5) {
		case 5: case 3: printf("nice 53 \n"); break;
		default: break;
	}

	if (argc !=3 ) {
		printf("usage %s, [ file ] [ sym ]\n", argv[0]);
		exit(-1);
	}

	if ((handle = dlopen(argv[1], RTLD_NOW)) != NULL) {
		func = dlsym(handle, argv[2]);
		if (func) {
			array[0] = argv[1];
			array[1] = NULL;
			printf("\n call routine\n");
			func(1, array);
		} else {
			printf("search sym: %s error: %s\n", argv[2], dlerror());
			exit(-2);
		}
	} else {
		printf("can not open: %s, error: %s\n", argv[1], dlerror());
		exit(-2);
	}

	exit(0);
}
