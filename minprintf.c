
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define LOCALFMT	100

void minprintf(char *fmt, ...)
{
	va_list ap;
	char	*p, *sval;
	char	localfmt[LOCALFMT];
	int		i, ival;
	unsigned uval;
	double	dval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
	}
}
