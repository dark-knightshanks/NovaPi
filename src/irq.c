
#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "entry.h"
#include "peripherals/irq.h"
#include "peripherals/timer.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};
void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
	printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}
void enable_interrupt_controller()
{
	//printf("enablr_interrupt_controller\n");
	*ENABLE_IRQS_1= SYSTEM_TIMER_IRQ_1;
}

void handle_irq(void)
{
    unsigned int irq = *IRQ_PENDING_1;
    
    printf("IRQ_PENDING_1: 0x%x\n", irq);
    
    // Check what bit is actually set
    for (int i = 0; i < 32; i++) {
        if (irq & (1 << i)) {
            printf("IRQ bit %d is set!\n", i);
        }
    }
    
    // Only call timer handler if timer interrupt is actually pending
    if (irq & SYSTEM_TIMER_IRQ_1) {
        printf("Timer interrupt confirmed\n");
        handle_timer_irq();
    } else {
        printf("NOT a timer interrupt! IRQ=0x%x\n", irq);
    }
}
