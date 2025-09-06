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

#define C_I2CEN			(1 << 15)
#define C_INTR			(1 << 10)
#define C_INTT			(1 << 9)
#define C_INTD			(1 << 8)
#define C_ST			(1 << 7)
#define C_CLEAR			(1 << 5)
#define C_READ			(1 << 0)

// Status register
#define S_CLKT			(1 << 9)
#define S_ERR			(1 << 8)
#define S_RXF			(1 << 7)
#define S_TXE			(1 << 6)
#define S_RXD			(1 << 5)
#define S_TXD			(1 << 4)
#define S_RXR			(1 << 3)
#define S_TXW			(1 << 2)
#define S_DONE			(1 << 1)
#define S_TA			(1 << 0)

#endif



 