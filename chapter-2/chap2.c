
/*
 * to lower char
 */
int lower(int c)
{
	return (c >= 'A') && (c <= 'Z') ? c - 'A' + 'a' : c;
}

/*
 * count the number of 1 bits in @s 
 */
int bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x &= (x - 1))	// faster
		b++;

	/*
	while (x != 0) {
		if (x & 1) b++;
		x = x >> 1;
	}
	*/
	return b;
}

static inline int wordlength(void)
{
	int	i;
	unsigned v = (unsigned )~0;
	for (i = 1; (v = v >> 1) > 0; i++)
		;
	return i;
}

/*
 * rotate x to the right by n positions
 */
unsigned rightrot(unsigned x, int n)
{
	int	rbit;

	while (n-- > 0) {
		rbit = (x & 1) << (wordlength() - 1);
		x = x >> 1;
		x = x | rbit;
	}
	return x;
}

/*
 * invert the @n bits of @x that begin at @p
 */
unsigned invert(unsigned x, int p, int n)
{
	/*
	 * my implementation
	 */
//	return ((~x) & (((1 << n) - 1) << p)) |
//		(x & (~(((1 << n) - 1) << p)));
	/*
	 * c book implementation
	 */
	return x ^ (((1 << n) - 1) << p);
}

/*
 * set y[0 ... n - 1] bits to the value of x[p ... p + n - 1] bits 
 * y's other bits keep unchanged;
 */
unsigned my_setbits(unsigned x, int p, int n, unsigned y)
{
	return (y & ~((1 << n) - 1)) | ((x & (((1 << n) - 1) << p)) >> p);
//	return x & ~(~(~0 << n) << (p + 1 - n)) |
//		(y & ~(~0 << n)) << (p + 1 - n);

}

/*
 * set x[p ... p + n - 1] to the value of y[0 ... n - 1];
 * x's other bits keep unchanged
 */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	/*
	 * could not understand why in c book need to (p + 1 - n) ???
	 * it seems that this is wrong
	 */
//	return x & ~(~(~0 << n) << (p + 1 - n)) |
//		(y & ~(~0 << n)) << (p + 1 - n);
	return x & ~(~(~0 << n) << (p)) |
		(y & ~(~0 << n)) << (p);
}

/*
 *
 *	return the position of char in @s1
 *	which first occur in @s1 and exist in @s2 too
 */
int any(const char *s1, const char *s2)
{
	int i;
	int j;

	for (j = 0; s2[j] != '\0'; j++) {
		for (i = 0; s1[i] != '\0'; i++)
			if (s2[j] == s1[i])
				return i;
	}

	return -1;
}


static void mov_str(char *s, int i)
{
	for ( ; s[i] != '\0'; i++)
		s[i] = s[i + 1];
}

/*
 * delete the char in @s1 which have the same char in @s2
 * first solution
 */
void squeeze(char *s1, const char *s2)
{
	int i; 
	int j;
	int	flag = 0;

	for (i = 0; s1[i] != '\0'; ) {
		for (j = 0; s2[j] != '\0'; j++) {
			if (s1[i] == s2[j]) {
				mov_str(s1, i);
				flag = 1;
				break;
			} 
		}
		if (flag) {
			flag = 0;
			i = 0;
		} else {
			i++;
		}
	}
}


/*
 * stand in c-l book
 */
void squeeze_c(char *s1, char *s2)
{
	int i, j, k;

	for (i = 0, k = 0; s1[i] != '\0'; i++) {
		for (j = 0; (s2[j] != '\0') && (s2[j] != s1[i]); j++)
			;
		if (s2[j] == '\0')
			s1[k++] = s1[i];
	}
	s1[k] = '\0';
}

/*
 * converts the digit in @s to int
 * the digit in @s is 0x or 0X
 */
int htoi(char *s)
{
	int	i = 0;
	int	value = 0;

	if (s[i] == '0') {
		i++;
		if ((s[i] == 'x') || (s[i] == 'X'))
			i++;
	}

	for ( ; ; i++) {
		if ((s[i] >= '0') && (s[i] <= '9'))
			value = value * 16 + s[i] - '0';
		else if ((s[i] >= 'a') && (s[i] <= 'f'))
			value = value * 16 + s[i] - 'a' + 10;
		else if ((s[i] >= 'A') && (s[i] <= 'F'))
			value = value * 16 + s[i] - 'A' + 10;
		else {
			break;
		}
	}

	return value;
}

/*
 * just for test routines above
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	/*
	 *  test htoi routine
	if (argc != 2) {
		printf("usage %s hexdigit\n", argv[0]);
		exit(1);
	}
	printf("str: %s , value: %d\n", argv[1], htoi(argv[1]));
	*/

	char	*p1 = NULL;
	char	*p2 = NULL;
	int		i;
	char	s1[1024];
	char	s2[1024];
	unsigned x, y;

	x = 0x000f;
	printf("x=0x%x right rot=0x%x\n", x, rightrot(x, 4));

	if (argc != 3) {
		printf("usage %s str1 str2\n", argv[0]);
		exit(1);
	}

	for (i = 0, p1 = argv[1]; (s1[i] = *p1) != '\0'; p1++, i++)
		;
	for (i = 0, p2 = argv[2]; (s2[i] = *p2) != '\0'; p2++, i++)
		;

	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
//	squeeze(s1, s2);
//	squeeze_c(s1, s2);
	printf("posi: %d\n", any(s1, s2));
	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);

	exit(0);
}
