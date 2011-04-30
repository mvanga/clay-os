#include <clay/module.h>
#include <clay/jiffies.h>
#include <clay/types.h>
#include <clay/io.h>
#include <clay/config.h>

#define SYSTICK_RELOAD 	0xE000E014
#define SYSTICK_COUNT	0xE000E018
#define SYSTICK_CTRL	0xE000E010

volatile u32 jiffies = INITIAL_JIFFIES;

void systick_handler(void)
{
	jiffies++;
}

int systick_init(void)
{
	/* Set the reload value */
	*REG(SYSTICK_RELOAD) = ((CPU_SPEED/HZ) & 0x00FFFFFF) - 1;
	/* Reset the count */
	*REG(SYSTICK_COUNT) = 0;
	/* Enable systick counter, interrupt and set clocksource to CPU */
	*REG(SYSTICK_CTRL) = (1 << 0) | (1 << 1) | (1 << 2);
	return 0;
}

void systick_exit(void)
{
	return;
}

module_init(systick_init);
module_exit(systick_exit);

void delay(int msec)
{
	u32 delay = jiffies + msecs_to_jiffies(msec);
	while (time_before(jiffies, delay));
}
