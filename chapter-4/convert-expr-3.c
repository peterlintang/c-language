
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

struct op_cmd {
	int type;
	void (*do_op)(int type, char s[]);
};

void do_left_bracket(int type, char s[])
{
	if (type == '(')
		push(type);
}

void do_right_bracket(int type, char s[])
{
	int op;

	if (type != ')') return;

	while ((op = pop()) != '(')
		fprintf(stdout, " %c ", op);
}

void do_plus(int type, char s[])
{
	int op;

	if (type != '+') return;

	do {
		op = pop();
// every time we add a new op's type, we need to update these too ?? how to solve this problem
		if (op == '=' || op == '(')
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

void do_sub(int type, char s[])
{
	int op;

	if (type != '-') return;

	do {
		op = pop();
// every time we add a new op's type, we need to update these too ?? how to solve this problem
		if (op == '=' || op == '(')
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

void do_mul(int type, char s[])
{
	int op;

	do {
		op = pop();
// every time we add a new op's type, we need to update these too ?? how to solve this problem
		if (op == '=' || op == '-' || op == '+' || op == '(')
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

void do_div(int type, char s[])
{
	int op;

	do {
		op = pop();
// every time we add a new op's type, we need to update these too ?? how to solve this problem
		if (op == '=' || op == '-' || op == '+' || op == '(')	
			break;
		fprintf(stdout, " %c ", op);
	} while (1);

	push(op);
	push(type);
}

void do_new_line(int type, char s[])
{
	int op;

	while ((op = pop()) != '=')
		fprintf(stdout, " %c ", op);
	push(op);
	fprintf(stdout, "\n");
}

void do_number(int type, char s[])
{
	fprintf(stdout, " %s ", s);
}

static struct op_cmd ops[] = {
	{ '-', do_sub },
	{ '+', do_plus },
	{ '*', do_mul },
	{ '/', do_div },
	{ '\n', do_new_line },
	{ '(', do_left_bracket },
	{ ')', do_right_bracket },
	{ NUMBER, do_number },
};

#define ARRAY_SIZE(s) (sizeof((s)) / sizeof((s[0])))

int main(int argc, char *argv[])
{
	int 	type;
	int		i;
	char 	s[1024];

	push('=');
	while ((type = getop(s)) != EOF) {
		for (i = 0; i < ARRAY_SIZE(ops); i++)
			if (ops[i].type == type) {
				ops[i].do_op(type, s);
				break;
			}
		if (i == ARRAY_SIZE(ops))
			fprintf(stderr, "unknow type: %c %d, i: %d, array_size: %d\n", 
					type, type, i, ARRAY_SIZE(ops));
	}

	exit(0);
}

