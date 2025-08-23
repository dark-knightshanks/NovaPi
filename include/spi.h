#ifndef SPI_H
#define SPI_H
#include <stdint.h>

void spi_init(void);
void spi_write(uint32_t data);

#endif