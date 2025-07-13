ENTRY(_start)

SECTIONS
{
    . = 0x80000; /* Raspberry Pi 4B firmware loads kernel8.img here */

    /* Code section */
    .text : ALIGN(4)
    {
        KEEP(*(.text.boot)) /* startup code */
        *(.text*)
    }

    /* Read-only data */
    .rodata : ALIGN(4)
    {
        *(.rodata*)
    }

    /* Initialized data */
    .data : ALIGN(4)
    {
        *(.data*)
    }

    /* Uninitialized data (zero-initialized by startup code) */
    .bss : ALIGN(8)
    {
    __bss_start = .;
    bss_begin = .;     /* <-- needed by boot.S */
    *(.bss*)
    *(COMMON)
    bss_end = .;       /* <-- needed by boot.S */
    __bss_end = .;
    }

}

