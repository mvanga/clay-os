#ifndef CLAY_STDIO_H
#define CLAY_STDIO_H

#include <stdarg.h>

int getc(void);
char *gets(char *s, int size);
void putc(int c);
void puts(char *s);
int vprintk(const char *fmt, va_list args);
int printk(const char *fmt, ...);
int sprintf(char * buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);

#endif
