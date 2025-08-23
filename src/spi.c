#include "printf.h"
#include "peripherals/spi.h"
#include <stdint.h>
#include "gpio.h"
#include "utils.h"

// Initializes the SPI0 peripheral.
void spi_init(void) {
    spi_gpio();
    CLK = 2048;
    CS &= ~(CS_CPOL | CS_CPHA);
    CS &= ~(3 << 0);
}

// Writes a single 32-bit value to the SPI bus.
void spi_write(uint32_t data) {
    DLEN = 4;
    CS |= CS_CLEAR_RX | CS_CLEAR_TX;
    CS |= CS_TA;

    while (!(CS & CS_TXD));
    FIFO = data;

    while (!(CS & CS_DONE));

    CS &= ~CS_TA;
}
