OUTPUT_ARCH(aarch64)
ENTRY(_start)

SECTIONS
{
	. = 0x80000;
	_text_boot = .;
	.text.boot : {
		*(.text.boot)
	}
	_etext_boot = .;
	_text = .;
	.text : {
		*(.text)
	}
	_etext = .;

	_rodata = .;
	.rodata : {
		*(.rodata)
	}
	_erodata = .;
	_data = .;
	.data : {
		*(.data)
		. = ALIGN(0x1000);
		*(.data.init_proc)
	}

	. = ALIGN(0x8);
	_edata = .;
	_bss = .;
	bss_begin = .;
	.bss : { *(.bss*) }
	bss_end = .;
	_ebss = .;
}