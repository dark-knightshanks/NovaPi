#ifndef  _P_SPI_H
#define  _P_SPI_H
#include "base.h"

#define CS       ((volatile unsigned int*)(PBASE + 0x00204000))
#define FIFO     ((volatile unsigned int*)(PBASE + 0x00204004))
#define CLK      ((volatile unsigned int*)(PBASE + 0x00204008))
#define DLEN     ((volatile unsigned int*)(PBASE + 0x0020400C))
#define LTOH     ((volatile unsigned int*)(PBASE + 0x00204010))
#define DC       ((volatile unsigned int*)(PBASE + 0x00204014))

#endif /*_P_SPI_H*/