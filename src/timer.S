.equ TIMER_BASE, 0xFE003000
.equ TIMER_CLO,  0x04    // Counter Lower 32-bits
.equ TIMER_CHI,  0x08    // Counter Higher 32-bits

.globl delay_timer
delay_timer:
    // Input: x0 = delay in microseconds
    stp x29, x30, [sp, #-32]!
    stp x19, x20, [sp, #16]
    mov x29, sp
    
    // Load timer base address
    ldr x19, =TIMER_BASE
    
    // Read current timer value (lower 32 bits)
    ldr w20, [x19, #TIMER_CLO]
    
    // Store original start time in w20 (we already have it)
    // No need for w21, use w20 as start time
    
wait_loop:
    // Read current timer value
    ldr w1, [x19, #TIMER_CLO]
    
    // Calculate elapsed time (handles wraparound)
    sub w2, w1, w20
    
    // Check if elapsed time >= delay
    cmp w2, w0
    blo wait_loop    // Branch if elapsed < delay
    
    // Restore registers and return
    ldp x19, x20, [sp, #16]
    ldp x29, x30, [sp], #32
    ret
