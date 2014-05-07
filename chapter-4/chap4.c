
/*
 * reverse @s 
 * use recursive
 * not correct and good
 */
#include <stdio.h>
char *__reverse_recursive(char s[], int low, int high)
{
	int 	i;
	char	tmp;
	int		mid;
	static int count = 0;

	printf("s: %s, count: %d\n", s, count);
	mid = low + (high - low) / 2;
	if (low < high) {
		__reverse_recursive(s, low, mid - 1);
		__reverse_recursive(s, mid + 1, high);
	}

	for (; mid < high; low++) {
		tmp = s[low];
		s[low] = s[++mid];
		s[mid] = tmp;
	}
	printf("s: %s, count: %d\n", s, count++);

	return s;
}

char *reverse_recursive(char s[])
{
	int len;
	for (len = 0; s[len] != '\0'; len++)
		;
	__reverse_recursive(s, 0, len - 1);
	return s;
}
/*
 * convert @num to string stored in @s
 * use recursive 	
 * hard to get the idea of using static variable
 */
#define private_abs(n) ((n) < 0 ? -(n) : (n))
char *itoa_recursive(int num, char s[])
{
	static int i = 0;

	if (num / 10) {
		itoa_recursive(num / 10, s);
	} else {
		if (num < 0) {
			s[i++] = '-';;
			num = -num;
		}
	}
	s[i++] = private_abs(num) % 10 + '0';
	s[i] = '\0';

	return s;
	/*
	if (num < 10) {
		s[0] = "0123456789"[num];
		s[1] = '\0';
	} else {
		s[0] = "0123456789"[num % 10];
		itoa_recursive(num / 10, &s[1]);
	}
	return s;
	*/
}

/*
 * getch ungetch :  buffered one char
 */
#include <stdio.h>	// for fprintf getchar
static int tmp_buf;
int getch()
{
	int c;

	if (tmp_buf != 0) {
		c = tmp_buf;
		tmp_buf = 0;
	} else
		c = getchar();
	return c;
}

void ungetch(int c)
{
	if (tmp_buf == 0)
		tmp_buf = c;
	else
		fprintf(stderr, "only support ungetch one char\n");
}

/*
 * second version of getch and ungetch, which can store BUF_SIZE chars
 */
#define BUF_SIZE	1024
static int tmp_buf_l[1024];
static int tmp_bufp = 0;
int getch_l()
{
	return (tmp_bufp > 0) ? tmp_buf_l[--tmp_bufp] : getchar();
}
void ungetch_l(int c)
{
	if (tmp_bufp >= BUF_SIZE)
		fprintf(stderr, "too many chars to unget, max: %d\n", BUF_SIZE);
	else
		tmp_buf_l[tmp_bufp++] = c;
}


/*
 * push string @s back on to input
 */
#include <stdio.h>	// stdin and ungetc
#define ungetch(c) ungetc(c, stdin)
void ungets(char s[])
{
	int len;

	for (len = 0; s[len] != '\0'; len++)
		;

	while (len-- > 0) 
		ungetch(s[len]);
}

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
	char	s[1024] = "hello  world";
	int 	value = 123;

	if (argc != 1) {
		printf("usage: %s int\n", argv[0]);
		exit(1);
	}
	printf("str: %s\n", s);
	printf("reverse: %s\n", reverse_recursive(s));
	exit(0);
}




