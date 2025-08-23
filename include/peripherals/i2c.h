#ifndef	_I2C_H
#define	_I2C_H

#include "base.h"

#define BSC1_BASE       (PBASE + 0x804000)

// I2C1 / BSC1 Registers
#define BSC1_C          REG32(BSC1_BASE + 0x00)   // Control
#define BSC1_S          REG32(BSC1_BASE + 0x04)   // Status
#define BSC1_DLEN       REG32(BSC1_BASE + 0x08)   // Data Length
#define BSC1_A          REG32(BSC1_BASE + 0x0C)   // Slave Address
#define BSC1_FIFO       REG32(BSC1_BASE + 0x10)   // FIFO Data
#define BSC1_DIV        REG32(BSC1_BASE + 0x14)   // Clock Divider
#define BSC1_DEL        REG32(BSC1_BASE + 0x18)   // Data Delay
#define BSC1_CLKT       REG32(BSC1_BASE + 0x1C)   // Clock Stretch Timeout




#endif 