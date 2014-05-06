
/*
 * implement the stack operations push pop
 */
#include <assert.h>	// for assert routine

#define STACK_MAX_ELEMENTS	1024
static int stack_pos = 0;
static double stack_array[STACK_MAX_ELEMENTS];

void push(double value)
{
//	assert(stack_pos < STACK_MAX_ELEMENTS);
	if (stack_pos < STACK_MAX_ELEMENTS)
		stack_array[stack_pos++] = value;
}

double pop(void)
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
#include <math.h>	// for sin cos exp pow routines


#define getch()	getchar()
#define ungetch(c)	ungetc(c, stdin)
#define NUMBER	'0'
#define NAME 'n'
#define	VERBOSE 'v'
#define VAR_TYPE 'x'

int getop(char s[])
{
	int	i;
	int	c;

	i = 0;
	while (((c = getch()) == ' ') || (c == '\t')) ;
	s[i++] = c;
	s[i] = '\0';

	i = 0;

	if (c == VERBOSE)
		return VERBOSE;
	if (isupper(c))
		return VAR_TYPE;

	if (islower(c)) {
		while (islower(s[++i] = c = getch())) ;
		s[i] = '\0';
		if (c != EOF)
			ungetch(c);
		if (i > 1)
			return NAME;
		else 
			return c;
	}

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

#define MAX_VAR	26
static int var_index;
static double vars[MAX_VAR];

struct op_cmd {
	int type;
	int (*do_op)(int type, char s[]);
}; 

static int do_sub(int type, char s[])
{
	double op1;
	double op2;

	op2 = pop();
	op1 = pop();
	push(op1 - op2);
	return 0;
}

static int do_plus(int type, char s[])
{
	double op1;
	double op2;

	op1 = pop();
	op2 = pop();
	push(op1 + op2);
	return 0;
}

static int do_mul(int type, char s[])
{
	double op1;
	double op2;

	op1 = pop();
	op2 = pop();
	push(op1 * op2);
	return 0;
}

static int do_div(int type, char s[])
{
	double op1;
	double op2;

	op2 = pop();
	op1 = pop();
	push(op1 / op2);
	return 0;
}

static int do_mod(int type, char s[])
{
	int op1;
	int op2;

	op2 = (int )pop();
	op1 = (int )pop();
	push(op1 % op2);
	return 0;
}

static int do_number(int type, char s[])
{
	push(atof(s));
	return 0;
}

static int do_new_line(int type, char s[])
{
	printf("result: %f\n", pop());
	return 0;
}

static int do_math(int type, char s[])
{
	double op1;
	double op2;

	if (!strcmp("sin", s)) {
		op1 = pop();
		push(sin(op1));
	} else if (!strcmp("cos", s)) {
		op1 = pop();
		push(cos(op1));
	} else if (!strcmp("exp", s)) {
		op1 = pop();
		push(exp(op1));
	} else if (!strcmp("pow", s)) {
		op1 = pop();
		op2 = pop();
		push(pow(op2, op1));
	} else {
		fprintf(stderr, "unkown math: %s\n", s);
	}
	return 0;
}

static int do_assign(int type, char s[])
{

	pop();	// useless
	vars[var_index] = pop();

	return 0;
}

static int do_print(int type, char s[])
{
	int i;

	for (i = 0; i < MAX_VAR; i++)
		fprintf(stderr, "var: %c, value: %f\n", 'A' + i, vars[i]);
}

static int do_var(int type, char s[])
{
	
	var_index = s[0] - 'A';
	push(vars[var_index]);
	return 0;
}

static struct op_cmd ops[] = {
	{ '-', do_sub },
	{ '+', do_plus },
	{ '*', do_mul },
	{ '/', do_div },
	{ '%', do_mod },
	{ NUMBER, do_number },
	{ NAME, do_math },
	{ '=', do_assign },
	{ VERBOSE, do_print },
	{ VAR_TYPE, do_var },
	{ '\n', do_new_line }
};

#define ARRAY_SIZE(s) (sizeof((s)) / sizeof((s)[0]))

int main(int argc, char *argv[])
{
	int i;
	int type;
	char s[1024];

	while ((type = getop(s)) != EOF) {
		for (i = 0; i < ARRAY_SIZE(ops); i++)
			if (ops[i].type == type) {
				ops[i].do_op(type, s);
				break;
			}
		if (i == ARRAY_SIZE(ops))
			fprintf(stderr, "unknow type: %d, %c\n", type, type);
	}

	exit(0);
}
