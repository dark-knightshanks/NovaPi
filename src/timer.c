#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "timer.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void timer_init(void)
{
    curVal = *TIMER_CLO;
    curVal += interval;
    *TIMER_C1 = curVal;
    printf("timer_init\n");
}
void handle_timer_irq(void)
{
    printf("IRQ Handler called!\n");
    printf("TIMER_CS before clear: 0x%x\n", *TIMER_CS);
    
    // This is the correct way to clear timer 1 interrupt
    *TIMER_CS = TIMER_CS_M1;  // Write 1 to bit 1 to clear it
    
    printf("TIMER_CS after clear: 0x%x\n", *TIMER_CS);
    
    // Set next interrupt
    *TIMER_C1 = *TIMER_CLO + interval;
    
    printf("Timer interrupt received\n\r");
}
