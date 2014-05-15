
#include <stdio.h>	// for size_t
/*
 *
 */
#define MAXLEN	1000	/* max len of line */
#define MAXSTOR	5000	/* size of available storage space */

int getline_c(char *s, int len)
{
	int total = 0;

	while ((len-- > 0) && ((*s = getchar()) != EOF) && (*s != '\n')) {
		s++; 
		total++;
	}

	return total;
}

char *strcpy_c(char *dst, const char *src);

int readlines(char *lineptr[], char *linestor, int maxlines)
{
	int		len;
	int		nlines;
	char 	line[MAXLEN];
	char	*p  = linestor;
	char	*linetop = linestor + MAXSTOR;	// how do it know the size of storage is MAXSTOR ???

	nlines = 0;
	while ((len = getline_c(line, MAXLEN)) > 0) {
		if ((nlines > maxlines) || ((p + len) > linetop))
			return -1;
		line[len] = '\0';
		strcpy_c(p, line);
		lineptr[nlines++] = p;
		p += len;
	}

	return nlines;
}

/*
 * libc routines;
 */
char *strcpy_c(char *dst, const char *src)
{
	char	*tmp = dst;
	while ((*dst++ = *src++) != '\0')
		;
	return tmp;
}

char *strncpy_c(char *dst, const char *src, size_t n)
{
	char	*tmp = dst;

	for (; (n > 0) && ((*dst++ = *src++) != '\0'); n--)
		;
	if (n <= 0)
		*dst = '\0';

	return tmp;
}

char *strncat_c(char *dst, const char *src, size_t n)
{
	char	*tmp = dst;

	while (*dst != '\0')
		dst++;

	for (; (n > 0) && ((*dst++ = *src++) != '\0'); n--)
		;
	if (n <= 0)
		*dst = '\0';

	return tmp;
}

int strncmp_c(const char *s1, const char *s2, size_t n)
{
	for (; (n > 0) && (*s1++ == *s2++); n--)
		;
	if (n == 0)
		return 0;
	s1--;
	s2--;
	return ((*s1 - *s2) > 0) ? 1 : -1;
}

/*
 * search whether @t exist in the end of @s
 * if not return 0;
 * if true return 1
 */
int strend(const char s[], const char t[])
{
	int s_len = 0;
	int t_len = 0;

	while (s[s_len] != '\0')
		s_len++;
	while (t[t_len] != '\0')
		t_len++;

	if (t_len > s_len) return 0;

	for (; t_len > 0;)
		if (s[--s_len] != t[--t_len])
			return 0;

	return 1;
}

/*
 * cat @t to the end of @s
 */
char *strcat_c(char *s, char *t)
{
	char *tmp = s;

	while (*tmp) 
		tmp++;

	while ((*tmp++ = *t++) != '\0')
		;
	return s;
}

#include <stdio.h>	// for ungetc getchar stdin
#define ungetch(c) ungetc(c, stdin)
/*
 * get float from input
 */
int getfloat(double *p)
{
	int c;
	int d;
	int sign = 1;
	int power = 0;

	while (isspace(c = getchar())) ;

	if (!isdigit(c) && (c != EOF) && 
			(c != '+') && (c != '-') && (c != '.')) {
		ungetch(c);
		return 0;
	}

	if (c == EOF) return c;

	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+' || c == '.') {
		d = c;
		c = getchar();
	}

	if (!isdigit(c)) {
		if (c != EOF)
			ungetch(c);
		ungetch(d);
		return d;
	}

	*p = 0.0;
	while (isdigit(c)) {
		*p = *p * 10 + (c - '0');
		c = getchar();
	}

	if (c == '.') {
		c = getchar();
		while (isdigit(c)) {
			*p = *p * 10 + (c - '0');
			power++;
			c = getchar();
		}
	}

	if (c != EOF)
		ungetch(c);

	for (; power > 0; power--) {
		*p /= 10;
	}

	*p *= sign;
	return c;
}

/*
 * get integer from input
 */
int getint(int *p)
{
	int c;
	int d;
	int sign;

	while (isspace(c = getchar())) ;

	if (!isdigit(c) && (c != EOF) && (c != '+') && (c != '-')) {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
		d = c;
		c = getchar();
	}

	if (!isdigit(c)) {
		if (c != EOF)
			ungetch(c);
		ungetch(d);
		return d;
	}

	*p = 0;
	while (isdigit(c)) {
		*p = *p * 10 + (c - '0');
		c = getchar();
	}

	if (c != EOF)
		ungetch(c);

	*p *= sign;
	return c;
}

/*
 * test routines
 */

#include <stdlib.h>

int main(int argc, char *argv[])
{
	int n = 0;
	double p;

	char s[] = "hello world";
	char t[] = "nice";
	fprintf(stdout, "%d %d\n", 'h', 'n');
	fprintf(stdout, "str: %s, str: %s, com: %d\n", s, t, strncmp_c(s, t, 8));
//	fprintf(stdout, "str: %s\n", strncpy_c(s, t, 7));
	fprintf(stdout, "str: %s\n", strncat_c(s, t, 5));
	fprintf(stdout, "str: %s\n", strcat_c(s, t));
	fprintf(stdout, "s: %s, t: %s end: %s\n", s, t, strend(s, t) ? "true" : "false");
//	while (getint(&n) != EOF)
	while (getfloat(&p) != EOF)
//	fprintf(stdout, "return: %c\n", getfloat(&p));
		fprintf(stdout, "p: %f\n", p);
	exit(0);
}
