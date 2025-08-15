#ifndef SPI_H
#define SPI_H
#include <stdint.h>

extern void spi_init(void);
extern void oled_command(void);
extern void oled_data(void);
extern void spi_write(uint8_t data);
extern void test_spi_pattern(void);
extern void oled_print_hello_world(void);
extern void test_oled_hello_world(void);
extern void spi_rx_tx_transfer_active(void);
extern void spi_transfer_stop(void);

#endif