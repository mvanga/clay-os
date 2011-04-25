#include <clay/uart.h>
#include <clay/stdio.h>
#include <stdarg.h>

#define PRINTK_BUFSIZE 128

static char printk_buf[PRINTK_BUFSIZE];

void puts(char *s)
{
	while (*s)
		uart_putc(*s++);
}

int vprintk(const char *fmt, va_list args)
{
	int ret;

	ret = vsprintf(printk_buf, fmt, args);
	puts(printk_buf);
	return ret;
}

int printk(const char *fmt, ...)
{
	va_list args;
	int r;

	va_start(args, fmt);
	r = vprintk(fmt, args);
	va_end(args);

	return r;
}
