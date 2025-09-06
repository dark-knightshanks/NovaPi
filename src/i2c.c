#include "peripherals/gpio.h"
#include "peripherals/i2c.h"
#include "printf.h"
#include <stdint.h>

// Initializes the I2C1 peripheral.
void i2c_init(void) {
    printf("Initializing I2C...\r\n");
    i2c_gpio();
    
    // Reset control register
    BSC1_C = 0;
    printf("BSC1_C after reset: 0x%08X\r\n", BSC1_C);
    
    // Clear FIFO and error/status flags
    BSC1_C = C_CLEAR;
    printf("BSC1_C after CLEAR: 0x%08X\r\n", BSC1_C);
    
    BSC1_S = S_CLKT | S_ERR | S_DONE;
    printf("BSC1_S after clear flags: 0x%08X\r\n", BSC1_S);
    
    printf("I2C initialization complete\r\n");
}


// Writes data to a slave over I2C.
int i2c_write(uint32_t slave_addr, uint32_t *tx_buffer, uint32_t dlen) {
    BSC1_A = slave_addr; // Slave address
    BSC1_DLEN = dlen; // Data length
    
    // Load data into FIFO
    for (uint32_t i = 0; i < dlen; i++) {
        BSC1_FIFO = tx_buffer[i];
    }
    
    // Start transfer
    BSC1_C = C_I2CEN | C_ST | C_CLEAR;
    
    // Wait for completion
    while (!(BSC1_S & S_DONE)) {}
    
    // Check for error
    if (BSC1_S & S_ERR) {
        return 1;
    }
    
    return 0;
}

// Reads data from a slave over I2C.
int i2c_read(uint32_t slave_addr, uint32_t *rx_buffer, uint32_t dlen) {
    BSC1_A = slave_addr; // Slave address
    BSC1_DLEN = dlen; // Data length
    
    // Start transfer with READ flag
    BSC1_C = C_I2CEN | C_ST | C_READ | C_CLEAR;
    
    // Wait for completion
    while (!(BSC1_S & S_DONE)) {}
    
    // Read data from FIFO
    for (uint32_t i = 0; i < dlen; i++) {
        while (!(BSC1_S & S_RXD)) {} // Wait until data available
        rx_buffer[i] = BSC1_FIFO;
    }
    
    // Check for error
    if (BSC1_S & S_ERR) {
        return 1;
    }
    
    return 0;
}