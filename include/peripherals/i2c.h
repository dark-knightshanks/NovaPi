#ifndef	_I2C_H
#define	_I2C_H

#include "base.h"

#define BSC1_BASE       (PBASE + 0x804000)

// I2C1 / BSC1 Registers
#define C          REG32(BSC1_BASE + 0x00)   // Control
#define S          REG32(BSC1_BASE + 0x04)   // Status
#define DLEN       REG32(BSC1_BASE + 0x08)   // Data Length
#define A          REG32(BSC1_BASE + 0x0C)   // Slave Address
#define FIFO       REG32(BSC1_BASE + 0x10)   // FIFO Data
#define DIV        REG32(BSC1_BASE + 0x14)   // Clock Divider
#define DEL        REG32(BSC1_BASE + 0x18)   // Data Delay
#define CLKT       REG32(BSC1_BASE + 0x1C)   // Clock Stretch Timeout




#endif