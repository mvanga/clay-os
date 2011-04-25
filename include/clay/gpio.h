#ifndef CLAY_GPIO_H
#define CLAY_GPIO_H

#define GPIO_INPUT	(0)
#define GPIO_OUTPUT	(~0)

#define GPIO_ON		1
#define GPIO_OFF	0

/* Macros to be used for GPIO ports */
#define GPIO_PIN(p, b)	((p) * 32 + (b))
#define GPIO_PORT(n)	(n / 32)
#define GPIO_BIT(n)		(n % 32)

void gpio_init(void);

void gpio_dir(int gpio, int dir);
void gpio_set(int gpio, int value);
int gpio_get(int gpio);

void gpio_dir_port(int port, int dir);
void gpio_set_port(int port, int value);
int gpio_get_port(int port);

#endif
