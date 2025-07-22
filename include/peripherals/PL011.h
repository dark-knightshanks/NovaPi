#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

//#define UART_BASE       (PBASE + 0x00201000)

#define UART_DR         ((volatile unsigned int*)(PBASE + 0x00201000))
#define UART_FR         ((volatile unsigned int*)(PBASE + 0x00201018))
#define UART_IBRD       ((volatile unsigned int*)(PBASE + 0x00201024))
#define UART_FBRD       ((volatile unsigned int*)(PBASE + 0x00201028))
#define UART_LCRH       ((volatile unsigned int*)(PBASE + 0x0020102c))
#define UART_CR         ((volatile unsigned int*)(PBASE + 0x00201030))
#define UART_IMSC       ((volatile unsigned int*)(PBASE + 0x00201038))
#define UART_ICR        ((volatile unsigned int*)(PBASE + 0x00201044))

#endif  /*_P_MINI_UART_H */