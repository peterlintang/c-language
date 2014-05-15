
/*
 *	qsort input lines and print them in order
 *	add support to reverse print
 *	add support to -f opt not condier upper lower case
 *	add support for -d opt to comp only alnum
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// for strcmp

#define MAXLINES	5000

int readlines(char *lines[], int nlines)
{
	int 	i;
	int		len;
	int		total = -1;
	char	*line = NULL;

	for (i = 0; i < nlines; i++) {
		if (getline(&line, &len, stdin) == -1)
			return total;
		total++;
		lines[total] = line;
		line = NULL;
	}

	return total;
}

void writelines(char *lines[], int nlines, int reverse)
{
	int i;

	if (reverse) {
		for (i = nlines - 1; i >= 0; i--) {
			fprintf(stdout, "%s", lines[i]);
			free(lines[i]);
		}
	} else  {
		for (i = 0; i < nlines; i++) {
			fprintf(stdout, "%s", lines[i]);
			free(lines[i]);
		}
	}
}

void swap(char *v[], int r1, int r2) 
{
	char	*tmp = NULL;
	tmp = v[r1];
	v[r1] = v[r2];
	v[r2] = tmp;
}

void qsort_c(char *v[], int left, int right,
		int (*comp)(void *, void *))
{
	int i;
	int last;

	if (left >= right)
		return ;

	swap(v, left, (left + right) / 2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (comp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort_c(v, left, last - 1, comp);
	qsort_c(v, last + 1, right, comp);
}

void usage(char *prog)
{
	fprintf(stdout, "%s [ -rhf ]\n", prog);
	exit(0);
}

int charcmp(char *s1, char *s2)
{
	for (; tolower(*s1) == tolower(*s2); s1++, s2++)
		if (*s1 == '\0')
			return 0;
	return tolower(*s1) - tolower(*s2);
}

int dircmp(char *s1, char *s2)
{
	char a;
	char b;
	fprintf(stdout, "in dir cmp\n");

	do {
		for (; (!isalnum(*s1)) && (*s1 != ' ') && (*s1 != '\0'); s1++)
			;
		a = *s1++;
		for (; (!isalnum(*s2)) && (*s2 != ' ') && (*s2 != '\0'); s2++)
			;
		b = *s2++;
		if ((a == b) && (a == '\0'))
			return 0;
	} while (a == b);
	return a - b;
}

int folddircmp(char *s1, char *s2)
{
	char a;
	char b;
	char *tmp_s1 = s1;
	char *tmp_s2 = s2;

	do {
		for (; (!isalnum(*s1)) && (*s1 != ' ') && (*s1 != '\0'); s1++)
			;
		a = tolower(*s1++);
		for (; (!isalnum(*s2)) && (*s2 != ' ') && (*s2 != '\0'); s2++)
			;
		b = tolower(*s2++);
		if ((a == b) && (a == '\0'))
			return 0;
	} while (a == b);
	return a - b;
}

int main(int argc, char *argv[])
{
	int 	opt;
	int		reverse = 0;
	int		fold = 0;
	int		dir	= 0;
	int		total = -1;
	char	*lines[MAXLINES];

	while ((opt = getopt(argc, argv, "rhfd")) != -1) {
		switch (opt) {
		case 'd':
			dir = 1;
			break;
		case 'r':
			reverse = 1;
			break;
		case 'f':
			fold = 1;
			break;
		case 'h':
			usage(argv[0]);
			break;
		default:
			fprintf(stderr, "unknow opt: %c\n", opt);
			break;
		}
	}

	if ((total = readlines(lines, MAXLINES)) >= 0) {
		if (dir && fold) {
			qsort_c(lines, 0, total, folddircmp);
		} else if (dir) {
			qsort_c(lines, 0, total, dircmp);
		} else if (fold) {
			qsort_c(lines, 0, total, charcmp);
		} else {
			qsort_c(lines, 0, total, strcmp);
		}
		writelines(lines, total + 1, reverse);
	}
	exit(0);
}

