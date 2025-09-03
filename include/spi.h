#ifndef SPI_H
#define SPI_H

extern void spi_init(void);
extern void display_logo(void);
extern void oled_command(void);
extern void oled_data(void);
extern void spi_write(unsigned char data);
extern void oled_clear_screen(void);
extern void oled_init(void);

#endif