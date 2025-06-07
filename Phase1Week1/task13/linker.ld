/* Linker script for RISC-V bare-metal program */

/* Define the entry point */
ENTRY(_start)

SECTIONS
{
    /* Define memory regions for code, data, and stack */
    . = 0x80000000; /* Start address for the program (adjust for your platform) */

    /* Text section (code) */
    .text : {
        *(.text)          /* All the code from the object files */
        *(.text.*)        /* Include any additional text sections (if applicable) */
    }

    /* Data section (initialized variables) */
    .data : {
        *(.data)          /* Initialized data variables */
    }

    /* BSS section (uninitialized variables) */
    .bss : {
        *(.bss)           /* Uninitialized global/static variables */
        *(COMMON)         /* Common uninitialized variables */
    }

    /* Heap section (for dynamic memory, if needed) */
    .heap : {
        . = ALIGN(8);
        PROVIDE(_heap_start = .);
        *(.heap)
        PROVIDE(_heap_end = .);
    }

    /* Stack section (for the stack memory) */
    .stack : {
        . = ALIGN(8);
        PROVIDE(_stack_start = .);
        *(.stack)
        PROVIDE(_stack_end = .);
    }

    /* End of program - used by crt0.S */
    .end : {
        PROVIDE(_end = .);
    }
}
