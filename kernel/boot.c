/*
 * BlackBoard OS
 * Author: Manohar Vanga
 * Released under the GNU GPLv2
 */

#include <clay/io.h>
#include <clay/config.h>

/* default handler if unspecified */
void default_handler(void)
{
	while (1);
}

extern u32 __text_end;
extern u32 __data_start;
extern u32 __data_end;
extern u32 __bss_start;
extern u32 __bss_end;

extern int main(void);

/* Do all preliminary work before starting the kernel */
void boot_init(void)
{
	u32 *src;
	u32 *dst;
	
	/* Copy the data segment into RAM */
	src = &__text_end;
	dst = &__data_start;
	while (dst < &__data_end)
		*dst++ = *src++;
	
	/* Zero the bss */
	dst = &__bss_start;
	while (dst < &__bss_end)
		*dst++ = 0;
	
	/* Start the kernel */
	main();
}

void irq_undef(void)
{
	return;
}

void systick_handler(void) __attribute__((weak, alias("irq_undef")));

/*
 * Define the vector table.
 * Note: The Cortex-M3 has a special criterion for validating our code.
 *       It expects the sum of the first 8 entries of the table to be 0.
 *       We have to thus add the first 7 entries in the table,
 *       negate that value, and place it in the reserved vector 7
 *       (assuming vectors 0 to 7). We do the checksum-ing and placement
 *       through an external small program.
 */
u32 *boot_vectors[] __attribute__ ((section("vectors"))) = {
	PTR(STACK_TOP),			/* Stack location */
	PTR(boot_init),			/* Main function to run */
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	PTR(systick_handler),
};
