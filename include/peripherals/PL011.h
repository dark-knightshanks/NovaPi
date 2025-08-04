#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

// Converted to volatile uint32_t*
#define UART_DR     REG32(PBASE + 0x00201000)
#define UART_FR     REG32(PBASE + 0x00201018)
#define UART_IBRD   REG32(PBASE + 0x00201024)
#define UART_FBRD   REG32(PBASE + 0x00201028)
#define UART_LCRH   REG32(PBASE + 0x0020102C)
#define UART_CR     REG32(PBASE + 0x00201030)
#define UART_IMSC   REG32(PBASE + 0x00201038)
#define UART_ICR    REG32(PBASE + 0x00201044)


#endif  /*_P_MINI_UART_H */