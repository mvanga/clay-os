#ifndef CLAY_JIFFIES_H
#define CLAY_JIFFIES_H

#include <clay/types.h>
#include <clay/config.h>

#define HZ 100
#if ((CPU_SPEED/HZ) & (~0x00FFFFFF))
#error "Systick reload value too high. Increase HZ."
#elif HZ > 1000
#error "Systick maximum frequency is 1000 Hz"
#elif (1000 % HZ)
#error "Systick HZ should be a factor of 1000"
#endif

#define INITIAL_JIFFIES ((unsigned long)(unsigned int)(-30 * HZ))

extern volatile u32 jiffies;

#define time_after(a,b)     ((long)(a) - (long)(b) > 0)
#define time_before(a,b)    time_after(b,a)
#define time_after_eq(a,b)  ((long)(a) - (long)(b) >= 0)
#define time_before_eq(a,b) time_after_eq(b,a)

u32 msecs_to_jiffies(const u32 m)
{
	return (m + (1000 / HZ) - 1) / (1000 / HZ);
}

u32 jiffies_to_msecs(const u32 j)
{
	return (1000 / HZ) * j;
}

void delay(int msec);

#endif
