
/*
 *	qsort input lines and print them in order
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

void writelines(char *lines[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++) {
		fprintf(stdout, "%s", lines[i]);
		free(lines[i]);
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

int main(int argc, char *argv[])
{
	int		total = -1;
	char	*lines[MAXLINES];

	if ((total = readlines(lines, MAXLINES)) >= 0) {
		qsort_c(lines, 0, total, strcmp);
		writelines(lines, total + 1);
	}
	exit(0);
}
