#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "peripherals/base.h"
#include <stdint.h>

#define GPFSEL0                 REG32(PBASE + 0x00200000)
#define GPFSEL1                 REG32(PBASE + 0x00200004)
#define GPFSEL2                 REG32(PBASE + 0x00200008)
#define GPFSEL4                 REG32(PBASE + 0x00200010)

#define GPSET0                  REG32(PBASE + 0x0020001C)
#define GPSET1                  REG32(PBASE + 0x00200020)
#define GPCLR0                  REG32(PBASE + 0x00200028)
#define GPCLR1                  REG32(PBASE + 0x0020002C)

#define GPIO_PUP_PDN_CNTRL_REG0 REG32(PBASE + 0x002000E4)
#define GPIO_PUP_PDN_CNTRL_REG1 REG32(PBASE + 0x002000E8)
#define GPIO_PUP_PDN_CNTRL_REG2 REG32(PBASE + 0x002000EC)


#define DC_PIN  24
#define RST_PIN 25

#endif  /*_P_GPIO_H */