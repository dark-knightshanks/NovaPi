#include "utils.h"
#include "peripherals/PL011.h"


void uart_send(char c)
{
    while (*UART_FR & (1 << 5)); // Wait until TX FIFO is not full
    *UART_DR = c;
}

char uart_recv(void)
{
    while (*UART_FR & (1 << 4)); // Wait while RX FIFO is empty
    return *UART_DR & 0xFF;
}

void uart_send_string(char* str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        uart_send(str[i]);
    }
}

void uart_init(void)
{
    
    pl011_gpio();
    // 3. Disable UART0 before configuring
    *UART_CR = 0x00000000;

    // 4. Clear pending interrupts
    *UART_ICR = 0x7FF;

    // 5. Set baud rate: 115200 (with UARTCLK = 48 MHz)
    *UART_IBRD = 26;  // Integer part (48MHz / (16 * 115200) = 26.04)
    *UART_FBRD = 3;   // Fractional part (0.04 * 64 + 0.5 = 3)

    // 6. Configure Line Control Register
    *UART_LCRH = (1 << 4) | (3 << 5);  // FIFO enabled, 8-bit word

    // 7. Enable UART, TX, RX
    *UART_CR = (1 << 0) | (1 << 8) | (1 << 9);  // UARTEN | TXE | RXE
}

void pl011_putc(void* p, char c)
{
    uart_send(c);
}
