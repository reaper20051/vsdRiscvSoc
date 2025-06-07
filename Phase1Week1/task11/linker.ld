ENTRY(_start)

SECTIONS
{
  /* Code (Flash) section */
  .text 0x00000000 :
  {
    *(.text*)     /* All code */
    *(.rodata*)   /* Read-only data like string literals */
  }

  /* Initialized data (SRAM) section */
  .data 0x10000000 :
  {
    *(.data*)     /* Initialized global/static vars */
  }

  /* Uninitialized data (BSS) section */
  .bss :
  {
    *(.bss*)      /* Uninitialized global/static vars */
    *(COMMON)
  }
}
