#ifndef	_P_BASE_H
#define	_P_BASE_H
                        

#include <stdint.h>
#define PBASE 0xFE000000
#define REG32(addr) (*(volatile uint32_t *)(addr))

#define CORE_CLOCK_SPEED 1500000000
#endif  /*_P_BASE_H */
