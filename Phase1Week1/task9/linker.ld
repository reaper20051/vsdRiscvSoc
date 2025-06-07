ENTRY(_start)

SECTIONS
{
	. = 0x80000000;

	.text : {
    	*(.text*)
	}

	.bss : {
    	*(.bss*)
    	. = ALIGN(4);
	}
}
