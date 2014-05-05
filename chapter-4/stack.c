
/*
 * implement the stack operations push pop
 * use static array to implement
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

