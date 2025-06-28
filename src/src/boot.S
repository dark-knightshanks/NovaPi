#include "mm.h"

.section ".text.boot"  // 
   

.global _start

_start:
    mrs    x0, mpidr_el1          // checks for processor id from mpidr_el1 system register 
    and    x0, x0,#0xFF          // Check processor id
    cbz    x0, master           // Hang for all non-primary CPU if the id matches it executes master 
    b    proc_hang

proc_hang: 
    b proc_hang             // hangs the rest of the cores 

master:
    adr    x0, bss_begin     // bss are empty variables
    adr    x1, bss_end
    sub    x1, x1, x0       // subtraction 
    bl     memzero          // goes to memzero

    mov    sp, #LOW_MEMORY   
    bl    kernel_main        // links to kernel_main 
