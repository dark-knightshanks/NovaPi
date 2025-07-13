#include "utils.h"
#include "peripherals/PL011.h"
#include "peripherals/gpio.h"

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
    // 1. Configure GPIO14 and GPIO15 to ALT0 (UART)
    unsigned int selector = *GPFSEL1;

    // Clear bits for GPIO14 (bits 12-14) and GPIO15 (bits 15-17)
    selector &= ~((7 << 12) | (7 << 15));
    // Set ALT0 (100 = 4) for GPIO14 and GPIO15
    selector |= (4 << 12) | (4 << 15);
    *GPFSEL1 = selector;

    // 2. Disable pull-up/down for GPIO14 and GPIO15
    unsigned int reg = *GPIO_PUP_PDN_CNTRL_REG0;
    reg &= ~((0b11 << 28) | (0b11 << 30)); // clear bits
    *GPIO_PUP_PDN_CNTRL_REG0 = reg;
    delay(150);  // wait for change to latch

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

void blink() {
    *GPFSEL2 |= (1 << 3);  // Set GPIO21 to output (bit 3)
    while (1) {
        *GPSET0 = (1 << 21);
        delay(1000000);
        *GPCLR0 = (1 << 21);
        delay(1000000);
    }
}
void pl011_putc(void* p, char c)
{
    uart_send(c);
}
