MEMORY
{
	ram (rwx) : ORIGIN = 0x10000000, LENGTH = 8K
	rom (rx) : ORIGIN = 0x00000000, LENGTH = 32K
}

SECTIONS
{
	.  = 0x0;
	.text : {
		*(vectors);
		*(.text);
		*(.rodata);
		__text_end = .;
	} > rom

	.text.module : {
		__init_start = .;
		*(.module0.init);
		*(.module1.init);
		*(.module2.init);
		__init_end = .;
		__exit_start = .;
		*(.module0.exit);
		*(.module1.exit);
		*(.module2.exit);
		__exit_end = .;
	} > rom

	. = 0x10000000;

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
