#ifndef CLAY_UART_H
#define CLAY_UART_H

void uart_init(void);

void uart_putc(int c);
int uart_getc(void);

#endif
