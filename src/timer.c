#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"
#include "common.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void timer_init ( void )
{
	curVal = TIMER_CLO;
	curVal += interval;
	TIMER_C1 = curVal;
}

void handle_timer_irq( void ) 
{
	curVal += interval;
	TIMER_C1 = curVal;
	TIMER_CS = TIMER_CS_M1;
	printf("Timer interrupt received\n\r");
}
u64 timer_get_ticks() {
    u32 hi = REGS_TIMER->counter_hi;
    u32 lo = REGS_TIMER->counter_lo;

    //double check hi value didn't change after setting it...
    if (hi != REGS_TIMER->counter_hi) {
        hi = REGS_TIMER->counter_hi;
        lo = REGS_TIMER->counter_lo;
    }

    return ((u64)hi << 32) | lo;
}

//sleep in milliseconds.
void timer_sleep(u32 ms) {
    u64 start = timer_get_ticks();

    while(timer_get_ticks() < start + (ms * 1000)) {

    }
}