#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

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

uint32_t timer_get_ticks() {
    uint32_t hi = TIMER_CHI;
    uint32_t lo = TIMER_CLO;

    //double check hi value didn't change after setting it...
    if (hi != TIMER_CHI) {
        hi = TIMER_CHI;
        lo = TIMER_CLO;
    }

    return (((uint64_t)hi << 32) | lo)/1000;
}