
/*
 * convert string to double
 * can deal with ***e(+-)** value
 */
double atof_c(const char s[])
{
	double value;
	double power;
	int i;
	int sign;
	int	exp;

	for (i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;
	if ((s[i] == '+') || (s[i] == '-'))
		i++;

	for (value = 0.0; isdigit(s[i]); i++) {
		value = value * 10.0 + (s[i] - '0');
	}

	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		value = value * 10.0 + (s[i] - '0');
		power *= 10.0;
	}

	value = sign * value / power;

	if ((s[i] == 'e') || (s[i] == 'E')) {
		i++;
		sign = (s[i] == '-') ? -1 : 1;
		if ((s[i] == '+') || (s[i] == '-'))
			i++;
		for (exp = 0; isdigit(s[i]); i++) {
			exp = 10 * exp + (s[i] - '0');
		}
		if (sign == 1) {
			while (exp-- > 0)
				value *= 10.0;
		} else {
			while (exp-- > 0)
				value /= 10.0;
		}
	}

	return value;
}
/*
 * convert string to double
 */
double atof_prv(const char s[])
{
	double left  = 0;
	double right = 0;
	int	count = 0;
	int	i;

	for (i = 0; s[i] != '\0'; i++) {
		if (isdigit(s[i])) {
			if (count) {
				right = right * 10 + (s[i] - '0');
				count++;
			} else {
				left = left * 10 + s[i] - '0';
			}
		} else if (s[i] == '.') {
			count = 1;
		} else
			break;
	}

	for (i = count; i > 1; i--) {
		right *= 0.1;
	}

	return (left + right);
}

/*
 * return the right most index of @t in @s, -1 if none
 */
int strrindex(char s[], char t[])
{
	int i;
	int j;
	int	k;
	int	pos = -1;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; (t[k] != '\0') && (s[j] == t[k]); j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			pos = i;
	}

	return pos;
}

int string_len(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return i + 1;
}

/*
 * return the right most index of @t in @s, -1 if none
 * but compare from back to front, faster
 */
int strrindex_fast(char s[], char t[])
{
	int i;
	int	j;
	int	k;

	i = string_len(s) - string_len(t);
	for ( ; i >= 0; i--) {
		for (j = i, k = 0; (t[k] != '\0') && (t[k] == s[j]); k++, j++)
			;
		if ((k > 0) && (t[k] == '\0'))
			return i;
	}

	return -1;
}


/*
 * test routines
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *p = "123.456";
	if (argc != 3) {
		printf("usage: %s double double\n", argv[0]);
		exit(1);
	}
	printf("str: %s value: %f\n", p, atof_prv(p));
	printf("str: %s value: %f\n", argv[1], atof_prv(argv[1]));
	printf("str: %s value: %f\n", argv[1], atof_c(argv[1]));
	printf("str: %s value: %f\n", argv[2], atof_c(argv[2]));
	exit(0);
}




