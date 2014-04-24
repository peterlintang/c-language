
/*
 * print the histogram of word length
 * modified from one-word-perline.c
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * my own implementation
 * mao shi li jie you dian cuo le 
int main(int argc, char *argv[])
{
#define IN_WORD		0
#define OUT_WORD	1

	int	state = OUT_WORD;
	int	c;
	int	count = 0;

	while ((c = getchar()) != EOF) {
		if (state == IN_WORD) {
			if ((c == '\n') || (c == ' ') || (c == '\t')) {
				printf(": ");
				int i;
				for ( i = 0; i < count; i++) {
					printf("*");
				}
				putchar('\n');
				state = OUT_WORD;
				count = 0;
			} else {
				putchar(c);
				count++;
			}
		} else if (state == OUT_WORD) {
			if ((c == '\n') || (c == ' ') || (c == '\t')) {
			} else {
				state = IN_WORD;
				putchar(c);
				count++;
			}
		}
	}

	exit(0);
}
 */

/*
 * c-l books implementation
 */
int main(int argc, char *argv[])
{

#define MAXHIST		20
#define MAXWORD		20
#define IN_WORD		0
#define OUT_WORD	1

	int	state = OUT_WORD;
	int	i;
	int j;
	int	nc;
	int	c;
	int	len;
	int	overflow;
	int maxvalue;
	int	wl[MAXWORD];

	nc = 0;
	overflow = 0;
	for (i = 0; i < MAXWORD; i++) {
		wl[i] = 0;
	}

	/*	this is the implementation in c-l books
	 */
	while ((c = getchar()) != EOF) {
		if ((c == '\n') || (c == ' ') || (c == '\t')) {
			state = OUT_WORD;
			if (nc > 0) {
				if (nc < MAXWORD)
					++wl[nc];
				else
					++overflow;
			}
			nc = 0;
		} else if (state == OUT_WORD) {
			state = IN_WORD;
			nc = 1;
		} else {
			++nc;
		}
	}

	maxvalue = 0;
	for (i = 1; i < MAXWORD; i++) {
		if (wl[i] > maxvalue)
			maxvalue = wl[i];
	}

	/*
	for (i = 1; i < MAXWORD; i++) {
		printf("%5d - %5d : ", i, wl[i]);
		if (wl[i] > 0) {
			if ((len = wl[i] * MAXHIST / maxvalue) <= 0)
				len = 1;
		} else 
			len = 0;
		while (len > 0) {
			putchar('*');
			--len;
		}
		putchar('\n');
	}
	if (overflow)
		printf("there are %d words >= %d\n", overflow, MAXWORD);
	*/
	maxvalue = 0;
	for (i = 1; i < MAXWORD; i++) {
		if (wl[i] > maxvalue)
			maxvalue = wl[i];
	}

	/*
	 * 
	 */
	for (i = MAXHIST; i > 0; i--) {
		for (j = 1; j < MAXWORD; j++) {
			if (wl[j] * MAXHIST / maxvalue >= i)
				printf(" * ");
			else
				printf("   ");
		}
		putchar('\n');
	}
	for (i = 1; i < MAXWORD; i++)
		printf("%4d ", i);
	putchar('\n');
	for (i = 1; i < MAXWORD; i++)
		printf("%4d ", wl[i]);
	putchar('\n');
	if (overflow)
		printf("there are %d words >= %d\n", overflow, MAXWORD);

	exit(0);
}
