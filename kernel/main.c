/*
 * BlackBoard OS
 * Author: Manohar Vanga
 * Released under the GNU GPLv2
 */

#include <clay/io.h>
#include <clay/gpio.h>
#include <clay/uart.h>
#include <clay/systick.h>
#include <clay/regs.h>
#include <clay/jiffies.h>
#include <clay/module.h>

void cpu_init(void)
{
	/* Turn on clock/power for IOCON block */
	*REG(AHBCLKCTRL) |= (1<<16);
}

void do_initcalls(void)
{
	initcall_t *call;
	call = &__init_start;
	do {
		(*call)();
		call++;
	} while (call < &__init_end);
}

void do_exitcalls(void)
{
	exitcall_t *call;
	/* Deinitialize in reverse */
	call = &__exit_end;
	call--;
	do {
		(*call)();
		call--;
	} while (call >= &__exit_start);
}

int main(void)
{
	cpu_init();
	do_initcalls();
	for (;;);
	do_exitcalls();
	for (;;);
}
