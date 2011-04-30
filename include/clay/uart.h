#ifndef CLAY_UART_H
#define CLAY_UART_H

void uart_init(void);

extern int __uart_getc(int);
#define uart_getc() __uart_getc(1)
#define uart_getc_noecho() __uart_getc(0)
void uart_putc(int c);

#endif
