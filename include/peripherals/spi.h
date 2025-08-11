#ifndef  _P_SPI_H
#define  _P_SPI_H
#include "peripherals/base.h"

#define CS       REG32(PBASE + 0x00204000)
#define FIFO     REG32(PBASE + 0x00204004)
#define CLK      REG32(PBASE + 0x00204008)
#define DLEN     REG32(PBASE + 0x0020400C)
#define LTOH     REG32(PBASE + 0x00204010)
#define DC       REG32(PBASE + 0x00204014)




#define CS_REN (0 << 6)
#define CS_LEN (0 << 5)
#define CS_CPHA (0 << 4)
#define CS_CPOL (0 << 3)
#define CS_1 (0 << 2)
#define CS_2 (0 << 1)
#define CS_0 (0 << 0)

#endif /*_P_SPI_H*/
