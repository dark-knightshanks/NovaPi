#ifndef  _P_SPI_H
#define  _P_SPI_H
#include "base.h"

#define CS       REG32(PBASE + 0x00204000)
#define FIFO     REG32(PBASE + 0x00204004)
#define CLK      REG32(PBASE + 0x00204008)
#define DLEN     REG32(PBASE + 0x0020400C)
#define LTOH     REG32(PBASE + 0x00204010)
#define DC       REG32(PBASE + 0x00204014)

#endif /*_P_SPI_H*/
