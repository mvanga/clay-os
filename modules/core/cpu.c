#include <clay/module.h>
#include <clay/regs.h>

int cpu_init(void)
{
	/* Turn on clock/power for IOCON block */
	*REG(AHBCLKCTRL) |= (1<<16);
}

void cpu_exit(void)
{
	return;
}

core_init(cpu_init);
core_exit(cpu_exit);
