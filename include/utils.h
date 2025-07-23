#ifndef	_UTILS_H
#define	_UTILS_H

extern void delay ( unsigned long);
extern int get_el(void);
extern void miniuart_gpio(void);
extern void pl011_gpio(void);
extern void spi_gpio(void); 
extern void oled_gpiocmd(void);
extern void oled_gpiodata(void);

#endif  /*_UTILS_H */