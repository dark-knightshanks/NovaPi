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
    // Simple cache disable approach
    // Step 1: Disable instruction cache immediately
    mrs x0, sctlr_el1
    bic x0, x0, #(1 << 12)      // Clear I-cache bit
    msr sctlr_el1, x0
    isb
    
    // Step 2: Invalidate instruction cache
    ic iallu
    dsb sy
    isb sy
    
    // Step 3: Disable data cache
    mrs x0, sctlr_el1  
    bic x0, x0, #(1 << 2)       // Clear C-cache bit
    msr sctlr_el1, x0
    dsb sy
    
    // Step 4: Simple data cache clean & invalidate
    mov x0, #0
clean_dcache_simple:
    dc csw, x0                  // Clean by set/way
    add x0, x0, #(1 << 5)       // Next cache line
    cmp x0, #(1 << 15)          // Simple bounds check
    b.lt clean_dcache_simple
    
    dsb sy
    
    // Step 5: Now disable MMU
    mrs x0, sctlr_el1
    bic x0, x0, #1              // Clear MMU bit  
    msr sctlr_el1, x0
    isb
    
    // Continue with EL2 -> EL1 transition
    ldr x0, =HCR_VALUE
    msr hcr_el2, x0
    
    ldr x0, =SPSR_VALUE
    msr spsr_el2, x0
    
    adr x0, el1_entry
    msr elr_el2, x0
    
    eret

// ---------------------------------------------
// EL1 Kernel Entry Point
el1_entry:
    // Clear BSS
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl  memzero
    
    // Set stack
    mov sp, #LOW_MEMORY
    
    // Jump to kernel
    bl  kernel_main
    
    b   proc_hang










//1.rpi os ssh , 2.replace kernel.img , 33.boot.S ,4.mini-uart/gpio registers problem


