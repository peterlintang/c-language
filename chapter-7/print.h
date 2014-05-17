#ifndef __MC_LIBC_PRINT_H
#define __MC_LIBC_PRINT_H

/*
 *  use the host env, 
 *  otherwise, implement your own va_start, 
 *  va_arg, va_end, and putchar routines.
 */
#include <stdarg.h>
#define PUTC(c)	putchar(c)

#define IBASE	10
#define OBASE	8
#define XBASE	16
#define ILETTER	"0123456789"
#define OLETTER "01234567"
#define XLETTER "0123456789abcdef"
#define NULL	0


int myprintf(const char *fmt, ...);
int minscanf(const char *fmt, ...);

#endif	// end of __MC_LIBC_PRINT_H
