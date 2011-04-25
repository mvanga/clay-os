#ifndef CLAY_STDIO_H
#define CLAY_STDIO_H

#include <stdarg.h>

void puts(char *s);
int vprintk(const char *fmt, va_list args);
int printk(const char *fmt, ...);
int sprintf(char * buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);

#endif
