#ifndef  _P_SPI_H
#define  _P_SPI_H
#include "peripherals/base.h"

#define CS       REG32(PBASE + 0x00204000)
#define FIFO     REG32(PBASE + 0x00204004)
#define CLK      REG32(PBASE + 0x00204008)
#define DLEN     REG32(PBASE + 0x0020400C)
#define LTOH     REG32(PBASE + 0x00204010)
#define DC       REG32(PBASE + 0x00204014)



#define CS_TXD		(1 << 18)
#define CS_RXD		(1 << 17)
#define CS_TA		(1 << 7)
#define CS_DONE		(1 << 16)
#define CS_CLEAR_RX	(1 << 5)
#define CS_CLEAR_TX	(1 << 4)
#define CS_CPOL     (1 << 3)
#define CS_CPHA      (1 << 2)

#endif /*_P_SPI_H*/
