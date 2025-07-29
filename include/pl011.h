#ifndef	_P_PL011_UART_H
#define	_P_PL011_UART_H


void uart_init ( void );
char uart_recv ( void );
void uart_send ( char c );
void uart_send_string(char* str);
void pl011_putc ( void* p, char c );


#endif  