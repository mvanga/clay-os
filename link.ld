MEMORY
{
	ram (rwx) : ORIGIN = 0x10000000, LENGTH = 8K
	rom (rx) : ORIGIN = 0x00000000, LENGTH = 32K
}

SECTIONS
{
	.  = 0x0;
	.text : {
		*(vectors)
		*(.text)
		*(.rodata)
	} > rom

	__text_end = .;

	. = 0x10001000;

	.data : {
		__data_start = .;
		*(.data)
		__data_end = .;
	} > ram AT > rom
	.bss : {
		__bss_start = .;
		*(.bss)
		__bss_end = .;
	} > ram AT > rom
}
