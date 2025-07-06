#ifndef	_MINI_UART_H
#define	_MINI_UART_H

void uart_init ( void );
char uart_recv ( void );
void uart_send ( char c );
void uart_send_string(char* str);
void putc ( void* p, char c );
void pl011_putc ( void* p, char c );
void muart_init ( void );
char muart_recv ( void );
void muart_send ( char c );
void muart_send_string(char* str);

#endif  /*_MINI_UART_H */