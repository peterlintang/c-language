
#define private_abs(x) ((x) < 0 ? -(x) : (x))

/*
 * convert int @n to @s in base @b
 */
char *itoa_b(int n, char s[], int b)
{
	int i, sign;
	int	j;
	int right;

	sign = n;
	i = 0;
	do {
		s[i++] = private_abs(n % b) + '0';
	} while ((n /= b) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	j = 0;
	i--;
	while ( j < i) {
		right = s[j];
		s[j] = s[i];
		s[i] = right;
		j++;
		i--;
	}
	return s;
}

/*
 * c book implementation
 */
char *itoa_c(int n, char s[])
{
	int i, sign;
	int	j;
	int right;

	sign = n;
	i = 0;
	do {
		s[i++] = private_abs(n % 10) + '0';
	} while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	j = 0;
	i--;
	while ( j < i) {
		right = s[j];
		s[j] = s[i];
		s[i] = right;
		j++;
		i--;
	}

	return s;
}

/*
 * convert @n to string
 */
char *itoa(int n, char s[])
{
	int sign = 0;
	int	j = 0;
	int i = 0;
	int	right;

	if (n < 0) {
		sign = 1;
		n = -n;
	}

	do {
		right = n % 10;
		n = n / 10;
		s[i++] = "0123456789"[right];
	} while (n);
	if (sign)
		s[i++] = '-';
	s[i] = '\0';

	i--;
	while ( j < i) {
		right = s[j];
		s[j] = s[i];
		s[i] = right;
		j++;
		i--;
	}

	return s;
}

/*
 * copy string from @s2 to @s1, 
 * expand a-z token to abc....xyz
 */
char *expand(char s1[], char s2[])
{
	int i;
	int j;
	int c;

	for (i = 0, j = 0; s2[i] != '\0'; i++) {
		switch (s2[i]) {
			case '-':
				i++;
				s1[j] = c + 1;
				c += 1;
				while (s2[i] > s1[j]) {
					s1[++j] = c + 1;
					c += 1;
				}
				j++;
				break;
			default:
				c = s2[i];
				s1[j++] = s2[i];
				break;
		}
	}
	s1[j] = '\0';

	return s1;
}

/*
 * copy str from @t to @s, 
 * and replace tab with \t and so on
 */
char  *escape(char s[], const char t[])
{
	int i;
	int j;

	for (i = 0, j = 0; t[i] != '\0'; i++) {
		switch (t[i]) {
		case '\t':
			s[j++] = '\\';
			s[j++] = 't';
			break;
		case '\n':
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		default:
			s[j++] = t[i];
			break;
		}
	}
	s[j] = '\0';
	return s;
}

/*
 * copy str from @t to @s, 
 * and replace \\t and so on with tab
 */
char *unescape(char s[], char t[])
{
	int i;
	int j;

	for (i = 0, j = 0; t[i] != '\0'; i++) {
		if (t[i] != '\\')
			s[j++] = t[i];
		else {
			switch (t[++i]) {
			case 't':
				s[j++] = '\t';
				break;
			case 'n':
				s[j++] = '\n';
				break;
			default:
				s[j++] = '\\';
				s[j++] = t[i];
				break;
			}
		}
	}
	s[j] = '\0';
	return s;
}

/*
 * test 
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char t[] = "hello	world\n";
	char t1[] = "hello	\\t\\nworld\n";
	char s[256];
	printf("t: %ss: %s\n", t, escape(s, t));
	printf("1: %ss: %s\n", t1, unescape(s, t1));
	printf("t: %s, expand: %s\n", "a-z0-9", expand(s, "a-z0-9"));
	printf("t: %d, itoa: %s\n", 123, itoa(123, s));
	printf("t: %d, itoa: %s\n", -123, itoa(-123, s));
	printf("t: %d, base: %d itoa: %s\n", 123, 7, itoa_b(123, s, 7));
	exit(0);
}



