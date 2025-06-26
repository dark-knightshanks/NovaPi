SECTIONS
{
    . = 0x80000; /* Load kernel at 0x80000 (Raspberry Pi standard) */

    .text.boot : { *(.text.boot) }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }

    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss*) }
    bss_end = .;
}
