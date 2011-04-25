#include <clay/gpio.h>
#include <clay/io.h>
#include <clay/types.h>
#include <clay/regs.h>

#define GPIO_BASE 	0x50000000
#define PORT_BASE 	0x10000

#define GPIO_DIR		0x8000
#define GPIO_DATA		0x3ffc

void gpio_init(void)
{
	/* Enable the GPIO clock */
	*REG(AHBCLKCTRL) |= (1 << 6);

	/* Set all pins to output */
	gpio_dir_port(0, GPIO_OUTPUT);
	gpio_dir_port(1, GPIO_OUTPUT);
	gpio_dir_port(2, GPIO_OUTPUT);
	gpio_dir_port(3, GPIO_OUTPUT);
}

void gpio_dir(int gpio, int dir)
{
	int port = GPIO_PORT(gpio);
	int bit = GPIO_BIT(gpio);
	if (port < 0 || port > 3)
		return;
	if (bit < 0 || bit > 11)
		return;

	volatile u32 *reg;
	reg = (volatile u32 *)(GPIO_BASE + PORT_BASE*port + GPIO_DIR);
	if (dir)
		*reg |= (1 << bit);
	else
		*reg &= ~(1 << bit);
}

void gpio_set(int gpio, int value)
{
	int port = GPIO_PORT(gpio);
	int bit = GPIO_BIT(gpio);
	volatile u32 *reg;
	if (port < 0 || port > 3)
		return;
	if (bit < 0 || bit > 11)
		return;
	reg = (volatile u32 *)(GPIO_BASE + PORT_BASE*port + GPIO_DATA);
	if (value)
		*reg &= ~(1 << bit);
	else
		*reg |= (1 << bit);
}

int gpio_get(int gpio)
{
	int port = GPIO_PORT(gpio);
	int bit = GPIO_BIT(gpio);
	if (port < 0 || port > 3)
		return -1;
	if (bit < 0 || bit > 11)
		return -1;

	volatile u32 *reg;
	reg = (volatile u32 *)(GPIO_BASE + PORT_BASE*port + GPIO_DATA);
	return ((*reg & (1<<bit)) ? 1 : 0);
}

void gpio_dir_port(int port, int dir)
{
	if (port < 0 || port > 3)
		return;

	dir = dir & 0xfff;
	volatile u32 *reg;
	reg = (volatile u32 *)(GPIO_BASE + PORT_BASE*port + GPIO_DIR);
	*reg = dir;
}

void gpio_set_port(int port, int value)
{
	if (port < 0 || port > 3)
		return;

	value = value & 0xfff;
	volatile u32 *reg;
	reg = (volatile u32 *)(GPIO_BASE + PORT_BASE*port + GPIO_DATA);
	*reg = value;
}

int gpio_get_port(int port)
{
	if (port < 0 || port > 3)
		return -1;

	volatile u32 *reg;
	reg = (volatile u32 *)(GPIO_BASE + PORT_BASE*port + GPIO_DATA);
	return *reg;
}
