#include <clay/module.h>
#include <clay/gpio.h>
#include <clay/jiffies.h>

int mytask_init(void)
{
	gpio_set(GPIO_PIN(3, 0), GPIO_ON);
	delay(1000);
	gpio_set(GPIO_PIN(3, 1), GPIO_ON);
	delay(1000);
	gpio_set(GPIO_PIN(3, 2), GPIO_ON);
	delay(1000);
	gpio_set(GPIO_PIN(3, 3), GPIO_ON);
	return 0;
}

void mytask_exit(void)
{
}

task_init(mytask_init);
task_exit(mytask_exit);
