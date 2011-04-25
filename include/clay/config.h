#ifndef CLAY_CONFIG_H
#define CLAY_CONFIG_H

/*
 * We place the stack at end of SRAM. The board has
 * (8KB of SRAM (0x2000) starting at 0x10000000).
 * Remember, it grows downwards!
 */
#define STACK_TOP 0x10002000

#define CPU_SPEED 12000000

#endif
