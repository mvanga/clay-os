#include <clay/module.h>
#include <clay/io.h>
#include <clay/regs.h>
#include <clay/types.h>

/* TXD and RXD pins */
#define IOCON_PIO1_6 		0x400440A4
#define IOCON_PIO1_7 		0x400440A8

/* UART Clock */
#define UARTCLKDIV			0x40048098

/* UART Registers */
#define UART_THR 			0x40008000
#define UART_RBR 			0x40008000
#define UART_IER 			0x40008004
#define UART_IIR 			0x40008008
#define UART_FCR 			0x40008008
#define UART_LCR 			0x4000800c
#define UART_LSR 			0x40008014

#define UART_DLL 			0x40008000
#define UART_DLM 			0x40008004
#define UART_FDR 			0x40008028

int uart_init(void)
{
	u32 div;

	/* Select correct functions for UART pins */
	*REG(IOCON_PIO1_6) = 1;
	*REG(IOCON_PIO1_7) = 1;

	/*
	 * Enable the UART peripheral clock. We cannot enable the
	 * clock without setting the divider so set to 1 for now 
	 */
	*REG(UARTCLKDIV) = 1;

	/* Enable clock/power for UART */
	*REG(AHBCLKCTRL) |= (1<<12);

	/*
	 * We now need to write the divisor for the baud rate.
	 * Access to the divisor registers requires setting of 
	 * DLAB bit (bit 7) in the UART's LCR (Line Control Register)
	 * We can disable this once we're done.
	 */
	*REG(UART_LCR) = (1 << 7);

	/*
	 * Baudrate = PCLK / (16*(256*UART_DLM + UART_DLL)*(1 + UART_FDR[0-3]/UART_FDR[4-7]))
	 * 115200 = 12000000 / (16*(256*x + y)*(1 + a/b))
	 * (256*x + y)*(1 + a/b) = 12000000 / (16 * 115200)
	 *                       = 6.510416667
	 * Let's take (256*x + y) = 4. Thus x = 0, y = 4
	 * This way (1 + a/b) = 1.627604167
	 * We can approximate it to (1 + 5/8)
	 */
	div = 4;
	*REG(UART_DLL) = div & 0xff;
	*REG(UART_DLM) = (div >> 8) & 0xff;
	*REG(UART_FDR) = (8 << 4) | 5; /* 1 + 5/8 */

	/* Reset DLAB and set word length to 8 bits, no parity, 1 stop bit */
	*REG(UART_LCR) = 0x3;

	/* Disable use of UART FIFOs. We can do it ourselves B-) */
	*REG(UART_FCR) = 0x0;
	return 0;
}

void uart_exit(void)
{
	return;
}

module_init(uart_init);
module_exit(uart_exit);

void uart_putc(int c)
{
	if (c == '\n')
		uart_putc('\r');
	/* Wait till the Transmitter Holding Register is empty */
	while (!(*REG(UART_LSR) & 0x20));
	/* Set the value in the Transmitter Holding Register */
	*REG(UART_THR) = c;
}

int __uart_getc(int echo)
{
	int c = 0;
	/* Wait till we have valid data */
	while(!(*REG(UART_LSR) & 1));
	c =  *REG(UART_RBR);
	if (c == '\r')
		c = '\n';
	if (echo)
		uart_putc(c);
	return c;
}
