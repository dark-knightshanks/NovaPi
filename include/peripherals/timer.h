#ifndef	_P_TIMER_H
#define	_P_TIMER_H

#include "peripherals/base.h"
#include "common.h"
#define TIMER_CS        REG32(PBASE+0x00003000)
#define TIMER_CLO       REG32(PBASE+0x00003004)
#define TIMER_CHI       REG32(PBASE+0x00003008)
#define TIMER_C0        REG32(PBASE+0x0000300C)
#define TIMER_C1        REG32(PBASE+0x00003010)
#define TIMER_C2        REG32(PBASE+0x00003014)
#define TIMER_C3        REG32(PBASE+0x00003018)

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

#define REGS_TIMER ((struct timer_regs *)(PBASE + 0x00003000))
struct timer_regs {
    reg32 control_status;
    reg32 counter_lo;
    reg32 counter_hi;
    reg32 compare[4];
};

#endif  /*_P_TIMER_H */