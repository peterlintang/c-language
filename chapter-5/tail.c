
/*
 * print the last @n (n default is 10) lines to stdout
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// for getopt

#define DEFAULT_PRINT_LINES	10
#define MAX_LENTH			1024

/*
 * module program, we see lines as an module
 * and support the below routines
 * lines variable and interfaces
 */
static int	lines_next_pos;	// the next empty index of line stored in @lines
static int	lines_total;		// the total effective lines in @lines
static int	lines_max;	// allowed max lines
static char **lines = NULL;	// store lines here

int lines_initialize(int maxlines)
{
	int i;

	lines = calloc(maxlines, sizeof(char *));
	if (!lines) {
		fprintf(stderr, "calloc error: %d \n", maxlines);
		return -1;
	}
	lines_next_pos = 0;
	lines_total = 0;
	lines_max = maxlines;
	/*
	fprintf(stdout, "total: %d, next: %d, max: %d\n", 
			lines_total, lines_next_pos, lines_max);
	for (i = 0; i < maxlines; i++)
		fprintf(stdout, "i: %d p: %p\n", i, lines[i]);
	fprintf(stdout, "sizeof(char *): %d\n", sizeof(char *));
	*/
	return 0;
}

int lines_insert(char *line)
{
	/*
	 * if the @lines is full, use @line replace the oldest line
	 */
	/*
	fprintf(stderr, "new line: %s, next: %d, total: %d, max: %d\n", 
			line, lines_next_pos, lines_total, lines_max);
	*/
	if (lines_total == lines_max)	{
		lines_next_pos = lines_next_pos % lines_max;
		if (lines[lines_next_pos]) {
			free(lines[lines_next_pos]);
			lines[lines_next_pos] = NULL;
		}
		lines[lines_next_pos++] = line;
	} else {
		lines_total++;
		lines[lines_next_pos++] = line;
	}
	return 0;
}

int lines_print(void)
{
	if (lines_total == lines_max) {
		while (lines_total-- > 0) {
			fprintf(stdout, "%s", lines[lines_next_pos % lines_max]);
			lines_next_pos++;
		}
	} else {
		for (lines_next_pos = 0; lines_next_pos < lines_total; lines_next_pos++)
			fprintf(stdout, "%s", lines[lines_next_pos]);
	}
	return 0;
}

void lines_destroy()
{
	int i;
	for (i = 0; i < lines_max; i++)
		if (lines[i]) {
			free(lines[i]);
			lines[i] = NULL;
		}
	free(lines);
	lines = NULL;
	lines_max = 0;
	lines_next_pos = 0;
	lines_total = 0;
}
/*
 * end of lines variable and interfaces
 */

int main(int argc, char *argv[])
{
	int 	opt;
	int		length = MAX_LENTH;
	char	*line = NULL;
	int 	maxlines = DEFAULT_PRINT_LINES;

	while ((opt = getopt(argc, argv, "n:")) != -1) {
		switch (opt) {
		case 'n':
			maxlines = atoi(optarg);
			break;
		default:
			fprintf(stderr, "unknow opt: %c\n", opt);
			break;
		}
	}

//	fprintf(stdout, "lines: %d\n", maxlines);
	if (lines_initialize(maxlines)) {
		fprintf(stderr, "init error: %d\n", maxlines);
		exit(-1);
	}

	while ((opt = getline(&line, &length, stdin)) != -1) {
		lines_insert(line);
		line = NULL;	// if not reset @line to null, 
						// getline will use the orig space to store the 
						// next line, which will replace the orig line
						// and will cause double free in lines_insert routine
	}
	lines_print();
	lines_destroy();

	exit(0);
}
