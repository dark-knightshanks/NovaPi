#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

#define UART_BASE       (PBASE+0x00201000)
#define UART_DR         ((volatile unsigned int*)(UART_BASE + 0x00))
#define UART_FR         ((volatile unsigned int*)(UART_BASE + 0x18))
#define UART_IBRD       ((volatile unsigned int*)(UART_BASE + 0x24))
#define UART_FBRD       ((volatile unsigned int*)(UART_BASE + 0x28))
#define UART_LCRH       ((volatile unsigned int*)(UART_BASE + 0x2c))
#define UART_CR         ((volatile unsigned int*)(UART_BASE + 0x30))
#define UART_IMSC       ((volatile unsigned int*)(UART_BASE + 0x38))
#define UART_ICR        ((volatile unsigned int*)(UART_BASE + 0x44))

#endif  /*_P_MINI_UART_H */