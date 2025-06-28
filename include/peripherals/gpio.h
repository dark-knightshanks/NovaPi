#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "peripherals/base.h"

#define GPFSEL1         ((volatile unsigned int*)(PBASE+0x00200004))
#define GPSET0          ((volatile unsigned int*)(PBASE+0x0020001C))
#define GPCLR0          ((volatile unsigned int*)(PBASE+0x00200028))
#define GPIO_PUP_PDN_CNTRL_REG0 ((volatile unsigned int*)(PBASE + 0x002000E4))



#endif  /*_P_GPIO_H */