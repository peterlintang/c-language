
/*
 * implement the stack operations push pop
 */
#include <assert.h>	// for assert routine

#define STACK_MAX_ELEMENTS	1024
static int stack_pos = 0;
static double stack_array[STACK_MAX_ELEMENTS];

void push(double value)
{
	assert(stack_pos < STACK_MAX_ELEMENTS);
	if (stack_pos < STACK_MAX_ELEMENTS)
		stack_array[stack_pos++] = value;
}

double pop(void)
{
	assert(stack_pos > 0);
	if (stack_pos > 0)
		return stack_array[--stack_pos];
	return 0;	// ???
}

/*
 * implement the getch ungetch routines
 */
/*
#define MAX_BUFFSIZE	1024
static int out_pos = 0;
static int in_pos  = 0;
static int local_buf[MAX_BUFFSIZE];
int getch()
{
}

void ungetch(int c)
{
}
*/

/*
 *	scan through the input and serach the operands and operaters
 */
#include <stdio.h>
#include <stdlib.h>


#define getch()	getchar()
#define ungetch(c)	ungetc(c, stdin)
#define NUMBER	'0'

int getop(char s[])
{
	int	i;
	int	c;

	i = 0;
	while (((c = getch()) == ' ') || (c == '\t')) ;
	s[i++] = c;
	s[i] = '\0';

	i = 0;
	if (!isdigit(c) && (c != '.') && (c != '-'))
		return c;

	if (c == '-') {
		if ((isdigit(c = getch())) || (c == '.'))
			s[++i] = c;
		else {
			if (c != EOF)
				ungetch(c);
			return '-';
		}
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/*
 * implement a very simple calculator
 */

int main(int argc, char *argv[])
{
	int type;
	double op1;
	double op2;
	char s[1024];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '-':
				op2 = pop();
				op1 = pop();
				push(op1 - op2);
				break;
			case '+':
				op1 = pop();
				op2 = pop();
				push(op1 + op2);
				break;
			case '*':
				op1 = pop();
				op2 = pop();
				push(op1 * op2);
				break;
			case '/':
				op2 = pop();
				op1 = pop();
				push(op1 / op2);
				break;
			case '\n':
				printf("result: %f\n", pop());
				break;
			default:
				printf("unknow type\n");
				break;
		}
	}

	exit(0);
}
