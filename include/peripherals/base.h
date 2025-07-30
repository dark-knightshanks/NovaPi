#ifndef	_P_BASE_H
#define	_P_BASE_H
                        

#include <stdint.h>
#define PBASE 0xFE000000
#define REG32(addr) (*(volatile uint32_t *)(addr))

#endif  /*_P_BASE_H */
