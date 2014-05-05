
/*
 * implement the stack operations push pop
 */
#include <assert.h>	// for assert routine

#define STACK_MAX_ELEMENTS	1024
typedef int	stack_element_t;
static int stack_pos = 0;
static stack_element_t stack_array[STACK_MAX_ELEMENTS];

void push(stack_element_t value)
{
//	assert(stack_pos < STACK_MAX_ELEMENTS);
	if (stack_pos < STACK_MAX_ELEMENTS)
		stack_array[stack_pos++] = value;
}

stack_element_t pop(void)
{
//	assert(stack_pos > 0);
	if (stack_pos > 0)
		return stack_array[--stack_pos];
	return 0;	// ???
}


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
 * convert express from middle to backend 
 * not dealing with (a....) * a format
 * just a + b - c * d / e + f formats
 * implement in some elegant ways ??? let's have a look on later
 * it seems that we dont have error handling , so ???
 */

void do_left_bracket(int type)
{
	if (type == '(')
		push(type);
}

void do_right_bracket(int type)
{
	int op;

	if (type != ')') return;

	while ((op = pop()) != '(')
		fprintf(stdout, " %c ", op);
}

void do_plus(int type)
{
	int op;

	if (type != '+') return;

	do {
		op = pop();
		if (op == '=' || op == '(')
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

void do_sub(int type)
{
	int op;

	if (type != '-') return;

	do {
		op = pop();
		if (op == '=' || op == '(')
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

void do_mul(int type)
{
	int op;

	do {
		op = pop();
		if (op == '=' || op == '-' || op == '+' || op == '(')
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

void do_div(int type)
{
	int op;

	do {
		op = pop();
		if (op == '=' || op == '-' || op == '+' || op == '(')
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

int main(int argc, char *argv[])
{
	int 	type;
	int		op;
	char 	s[1024];

	push('=');
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case '(':
			do_left_bracket(type);
			break;
		case ')':
			do_right_bracket(type);
			break;
		case NUMBER:
			fprintf(stdout, " %s ", s);
			break;
		case '-':
			do_sub(type);
			break;
		case '+':
			do_plus(type);
			break;
		case '*':
			do_mul(type);
			break;
		case '/':
			do_div(type);
			break;
		case '\n':
			while ((op = pop()) != '=')
				fprintf(stdout, " %c ", op);
			push(op);
			fprintf(stdout, "\n");
			break;
		default:
			fprintf(stderr, "unknow type: %d\n", type);
			break;
		}
	}

	exit(0);
}

