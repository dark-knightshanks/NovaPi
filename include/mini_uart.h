#ifndef	_MINI_UART_H
#define	_MINI_UART_H


void putc ( void* p, char c );
void muart_init ( void );
char muart_recv ( void );
void muart_send ( char c );
void muart_send_string(char* str);
void print_uart_registers(void);
#endif  /*_MINI_UART_H */