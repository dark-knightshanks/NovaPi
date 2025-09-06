#include "peripherals/gpio.h"
#include "utils.h"
#include "printf.h"
#include "gpio.h"

void set_gpfsel(unsigned int pin, unsigned int mode) {
    if (pin > 57 || mode > 7) return; // Basic bounds checking
    unsigned int reg_index = pin / 10;
    unsigned int bit_offset = (pin % 10) * 3;
    volatile unsigned int *gpfsel = &GPFSEL0 + reg_index;

    *gpfsel &= ~(7 << bit_offset);
    *gpfsel |= (mode << bit_offset);
}

void set_gpio_pull(unsigned int pin, unsigned int pull_mode) {
    if (pin > 57 || pull_mode > 2) return; // Basic bounds checking
    unsigned int reg_index = pin / 16;
    unsigned int bit_offset = (pin % 16) * 2;
    volatile unsigned int *gpiopupdnctrl = &GPIO_PUP_PDN_CNTRL_REG0 + reg_index;

    *gpiopupdnctrl &= ~(3 << bit_offset);
    *gpiopupdnctrl |= (pull_mode << bit_offset);
}

// Fixed GPIO configuration for Pi 4B UART
void pl011_gpio(){
    // Configure GPIO14 and GPIO15 to ALT0 (UART)
    set_gpfsel(14, 4); // ALT0 for GPIO14
    set_gpfsel(15, 4); // ALT0 for GPIO15

    // Disable pull-up/down for GPIO14 and GPIO15
    set_gpio_pull(14, 0); // No pull for GPIO14
    set_gpio_pull(15, 0); // No pull for GPIO15

    delay(150); // Wait for changes to take effect
}

// Alternative - try Mini UART instead of PL011
void miniuart_gpio(){
    // Configure GPIO14 and GPIO15 to ALT5 (Mini UART)
    set_gpfsel(14, 2); // ALT5 for GPIO14
    set_gpfsel(15, 2); // ALT5 for GPIO15

    // Disable pull-up/down for GPIO14 and GPIO15
    set_gpio_pull(14, 0); // No pull for GPIO14
    set_gpio_pull(15, 0); // No pull for GPIO15
}

void spi_gpio(){
    // Configure GPIO8, GPIO10, GPIO11 for SPI0
    set_gpfsel(8, 4);  // ALT0 for GPIO8 (CE0)
    set_gpfsel(10, 4); // ALT0 for GPIO10 (MOSI)
    set_gpfsel(11, 4); // ALT0 for GPIO11 (SCLK)

    // Disable pull-up/down for SPI pins
    set_gpio_pull(8, 0);
    set_gpio_pull(10, 0);
    set_gpio_pull(11, 0);
}

void oled_gpiocmd(){
    GPCLR0 = (1 << 24);
}

void oled_gpiodata(){
    GPSET0 = (1 << 24);
}


void i2c_gpio() {
    
    unsigned int selector = GPFSEL0;
   
    selector &= ~((7 << 6) | (7 << 9));

    selector |= (4 << 6) | (4 << 9);
    GPFSEL0 = selector;

    
    unsigned int reg = GPIO_PUP_PDN_CNTRL_REG0;
    reg &= ~((0b11 << 4) | (0b11 << 6));  
    GPIO_PUP_PDN_CNTRL_REG0 = reg;

    delay(150); 
}