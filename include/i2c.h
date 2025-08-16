
#ifndef I2C_H
#define I2C_H

#include <stdint.h> // for uint32_t

int i2c_init(void);
int i2c_write(uint32_t slave_addr, uint32_t *tx_buffer, uint32_t dlen);
int i2c_read(uint32_t slave_addr, uint32_t *rx_buffer, uint32_t dlen);

#endif
