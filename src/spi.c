#include "printf.h"
#include "peripherals/spi.h"
#include <stdint.h>
#include "utils.h"

// Initializes the SPI0 peripheral.
void spi_init(void) {
    printf("Starting SPI initialization\r\n");
    
    spi_gpio();
    printf("GPIO configured for SPI\r\n");
    
    CLK = 512;
    printf("Clock divisor set to: %d\r\n", 256);
    
    CS &= ~(CS_CPOL | CS_CPHA);
    printf("Clock polarity and phase cleared\r\n");
    
    CS &= ~(3 << 0);
    printf("Chip select cleared\r\n");
    
    printf("SPI init complete. Final CS: 0x%08X\r\n", CS);
}
// Writes a single 32-bit value to the SPI bus.
void spi_write(uint32_t data) {
    printf("Starting SPI write with data: 0x%08X\n", data);
    
    DLEN = 4;
    CS |= CS_CLEAR_RX | CS_CLEAR_TX;
    CS |= CS_TA;
    
    printf("CS after setup: 0x%08X\n", CS);
    
    while (!(CS & CS_TXD));
    printf("TX ready, writing to FIFO\n");
    
    FIFO = data;
    printf("Data written to FIFO: 0x%08X\n", data);
    
    while (!(CS & CS_DONE));
   //ntf("Transfer complete\n");
    
    CS &= ~CS_TA;
    printf(" 0x%08X\r\n", CS);
}