
/*
 * compare tow files and print the first diff lines
 */
#include <stdio.h>
#include <stdlib.h>

int getline_c(FILE *in, char *s, int lim)
{
	int total = 0;

	while ((lim-- > 0) && ((s[total] = getc(in)) != EOF)) {
		if (s[total] != '\n') {
			total++;
			continue;
		}
		total++;
		break;
	}
	return total;
}

void usage(char *s)
{
	fprintf(stderr, "usage: %s file1 file2\n", s);
	exit(-1);
}

#define MAXLINE	1024

int main(int argc, char *argv[])
{
	FILE *f1 = NULL;
	FILE *f2 = NULL;
	int len1;
	int len2;
	char line1[MAXLINE];
	char line2[MAXLINE];

	if (argc != 3)
		usage(argv[0]);
	f1 = fopen(argv[1], "r");
	f2 = fopen(argv[2], "r");
	if (!f1 || !f2) {
		fclose(f1);
		fclose(f2);
		fprintf(stderr, "failed to open file: %s %s\n", 
				argv[1], argv[2]);
		exit(-1);
	}

	/*
	while ((len1 = getline_c(f1, line1, MAXLINE)) > 0) {
		line1[len1] = '\0';
		fprintf(stdout, "%s", line1);
	}
	*/
	while ((len1 = getline_c(f1, line1, MAXLINE)) > 0 
			&& (len2 = getline_c(f2, line2, MAXLINE)) > 0) {
		line1[len1] = '\0';
		line2[len2] = '\0';
		if (strcmp(line1, line2) != 0) {
			fprintf(stdout, "first diff lines\n");
			fprintf(stdout, "file: %s line: %s\n", argv[1], line1);
			fprintf(stdout, "file: %s line: %s\n", argv[2], line2);
			break;
		}
	}

	fclose(f1);
	fclose(f2);
	exit(0);
}
