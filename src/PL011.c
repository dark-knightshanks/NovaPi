#include "utils.h"
#include "peripherals/PL011.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	while(1) {
		if((*UART_FR)& (1<<5)) 
			break;
	}
	*UART_DR=c;
}

char uart_recv ( void )
{
	while(1) {
		if((*UART_FR)&(1<<6)) 
			break;
	}
	return((*UART_DR)&0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}
void uart_init ( void )
{
    unsigned int selector;

    selector = *GPFSEL3;
    selector &= ~(7 << 6);   // Clear bits 6–8 for GPIO32
    selector |=  (3 << 6);   // Set ALT3 (011) for GPIO32

    selector &= ~(7 << 9);   // Clear bits 9–11 for GPIO33
    selector |=  (3 << 9);   // Set ALT3 (011) for GPIO33
                
    *GPFSEL3 = selector;


    // Clear pull-up/down settings for GPIO 14 and 15 (each pin uses 2 bits)
    unsigned int reg = *GPIO_PUP_PDN_CNTRL_REG2;

    reg &= ~((0b11 << (0 * 2)) | (0b11 << (1 * 2)));  // Clear bits for GPIO32 and GPIO33

    *GPIO_PUP_PDN_CNTRL_REG2 = reg;

   // Disable UART
   *UART_CR = 0x00000000;

   // Clear pending interrupts
   *UART_ICR = 0x7FF;

   // Set integer & fractional baud rate (115200 baud if UART_CLK = 48 MHz)
   *UART_IBRD = 26;  // Integer part
   *UART_FBRD = 3;   // Fractional part

   // Line Control: 8 bits, no parity, 1 stop bit, FIFOs enabled
   *UART_LCRH = (1 << 4) | (1 << 5) | (1 << 6); // 8-bit word length, FIFO enabled

   // Enable UART, TX and RX
   *UART_CR = (1 << 0) | (1 << 8) | (1 << 9);  // UARTEN, TXE, RXE
}
