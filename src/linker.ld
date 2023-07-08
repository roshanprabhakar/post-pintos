ENTRY(start)

start_addr = 0x80000;

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
		. = ALIGN(8);
		bss_end = .;
	}

	bss_size = bss_end - bss_start;
	end = .;
}

