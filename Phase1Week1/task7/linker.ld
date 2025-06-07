
ENTRY(_start)

MEMORY {
  FLASH (rx) : ORIGIN = 0x80000000, LENGTH = 512K
  RAM   (rwx): ORIGIN = 0x80080000, LENGTH = 512K
}

SECTIONS {
  .text : {
	*(.init)
	*(.text*)
	*(.rodata*)
  } > FLASH

  .data : {
	*(.data*)
  } > RAM

  .bss : {
	*(.bss*)
	*(COMMON)
  } > RAM
}
