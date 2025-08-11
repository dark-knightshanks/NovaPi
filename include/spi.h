#ifndef SPI_H
#define SPI_H

extern void spi_init(void);
extern void oled_command(void);
extern void oled_data(void);
extern void spi_write(unsigned char data);
extern void test_spi_pattern(void);
extern void oled_print_hello_world(void);
extern void test_oled_hello_world(void);

#endif