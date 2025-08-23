#ifndef GPIO_H
#define GPIO_H

void set_gpfsel(unsigned int pin, unsigned int mode);
void set_gpio_pull(unsigned int pin, unsigned int pull_mode);

void pl011_gpio(void);
void miniuart_gpio(void);
void spi_gpio(void);
void oled_gpiocmd(void);
void oled_gpiodata(void);
void i2c_gpio(void);

#endif