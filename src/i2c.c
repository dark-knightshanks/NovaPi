#include "peripherals/i2c.h"
#include "peripherals/gpio.h"
#include <stdint.h>

/* This can be used to initialize the I2C controller and set their initial values */
int i2c_init(void) {
    /* this will set GPIO pins for SDA and SCL to ALT0 */
    gpio_set_alt(I2C_SDA_PIN, GPIO_ALT0);
    gpio_set_alt(I2C_SCL_PIN, GPIO_ALT0);
    /*this will reset control register*/ 
    BSC1_C = 0;
    /*this will clear FIFO and will clear the error flags*/ 
    BSC1_C = BSC_C_CLEAR;
    BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;

    return 0; 
}

/* This will broadcast the given slave address, wait and write the data, and will also know when to stop writing */
int i2c_write(uint32_t slave_addr, uint32_t *tx_buffer, uint32_t dlen) {
    /*this will set which slave to talk to*/ 
    BSC1_A = slave_addr;      
    /*this will decide the number of bytes of data*/
    BSC1_DLEN = dlen;        
    /*this will add data into FIFO */ 
    for (uint32_t i = 0; i < dlen; i++) {
        BSC1_FIFO = tx_buffer[i];
    }
    /* this will enable I2C controller,start transfer,clear FIFO */
    BSC1_C = BSC_C_I2CEN | BSC_C_ST | BSC_C_CLEAR;
    /* this will wait for completion */   
    while (!(BSC1_S & BSC_S_DONE)) {}
    /* this will check for any error */ 
    if (BSC1_S & BSC_S_ERR){ 
        return 1;  
    }
    return 0;
}

/* This will broadcast the given slave address, wait and read the data, and will also know when to stop reading */
int i2c_read(uint32_t slave_addr, uint32_t *rx_buffer, uint32_t dlen) {
    /*this will set which slave to talk to*/ 
    BSC1_A = slave_addr;      
    /*this will decide the number of bytes of data*/
    BSC1_DLEN = dlen;        
    /* this will enable I2C controller,start transfer,indicate read operation instead of write,clear FIFO */
    BSC1_C = BSC_C_I2CEN | BSC_C_ST | BSC_C_READ | BSC_C_CLEAR;
    /* this will wait until done flag is set */
    while (!(BSC1_S & BSC_S_DONE)) {}
    /* this will read the data */
    for (uint32_t i = 0; i < dlen; i++) {
        while (!(BSC1_S & BSC_S_RXD)) {} // wait for data
        rx_buffer[i] = BSC1_FIFO;
    }
    /* this will check for any error */ 
    if (BSC1_S & BSC_S_ERR){ 
        return 1;  
    }
    return 0;
}