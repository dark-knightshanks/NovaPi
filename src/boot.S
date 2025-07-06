#include "sysregs.h"
#include "mm.h"

.section ".text.boot"

.globl _start
_start:
    // Read core ID and halt non-core 0
    mrs x0, mpidr_el1
    and x0, x0, #0xFF
    cbz x0, master
    b proc_hang

proc_hang:
    b proc_hang

master:
    // Disable MMU at EL1
    ldr x0, =SCTLR_VALUE_MMU_DISABLED
    msr sctlr_el1, x0

    // Disable virtualization traps at EL2
    ldr x0, =HCR_VALUE
    msr hcr_el2, x0          // HCR_EL2 = 0

    // Set EL1h mode and mask interrupts
    ldr x0, =SPSR_VALUE
    msr spsr_el2, x0         // SPSR_EL2 ← EL1h

    // Set ELR_EL2 to el1_entry
    adr x0, el1_entry
    msr elr_el2, x0

    // Go to EL1
    eret

// ---------------------------------------------
// EL1 Kernel Entry Point
el1_entry:
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl  memzero

    mov sp, #LOW_MEMORY
    bl  kernel_main
    b   proc_hang           // should never return


