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

void cpu_init(void)
{
	/* Turn on clock/power for IOCON block */
	*REG(AHBCLKCTRL) |= (1<<16);
}

int main(void)
{
	cpu_init();
	gpio_init();
	uart_init();
	systick_init();

	/* Run the test LED */
	gpio_set(GPIO_PIN(3, 0), GPIO_ON);
	delay(1000);
	gpio_set(GPIO_PIN(3, 1), GPIO_ON);
	delay(1000);
	gpio_set(GPIO_PIN(3, 2), GPIO_ON);
	delay(1000);
	gpio_set(GPIO_PIN(3, 3), GPIO_ON);

	for (;;);
}
