ENTRY(start)

start_addr = 0x80000;
end_addr = 0x40000000;

SECTIONS
{
	. = start_addr;
	.text : { KEEP(*(.text.boot)) *(.text*) }

	.rodata : { *(.rodata*) }

	PROVIDE (data_section = .);
	.data : { *(.data*) }

	.bss (NOLOAD) : {
		. = ALIGN(16);
		bss_start = .;
		*(.bss*)
		. = ALIGN(4096);
		bss_end = .;
	}

	bss_size = bss_end - bss_start;
	kernel_end = .;
}

