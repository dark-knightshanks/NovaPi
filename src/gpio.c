#include "peripherals/gpio.h"
#include "printf.h"


void setALT(int gpio, int alt_function) {
    volatile unsigned int* gpfsel;
    int bit_offset;
    
    if (gpio <= 9) {
        gpfsel = &GPFSEL0;
        bit_offset = gpio * 3;
    } else if (gpio <= 19) {
        gpfsel = &GPFSEL1;
        bit_offset = (gpio - 10) * 3;
    } else if (gpio <= 29) {
        gpfsel = &GPFSEL2;
        bit_offset = (gpio - 20) * 3;
    } else {
        return; // Invalid GPIO
    }
    
    // Clear the 3 bits for this GPIO
    *gpfsel &= ~(7 << bit_offset);
    
    // Set the alternate function (or output if alt_function = 1)
    *gpfsel |= (alt_function << bit_offset);
}

void clearPullUpDown(int gpio) {
    volatile unsigned int* reg;
    int bit_offset;
    
    if (gpio <= 15) {
        reg = &GPIO_PUP_PDN_CNTRL_REG0;
        bit_offset = gpio * 2;  // Each GPIO uses 2 bits
    } else if (gpio <= 31) {
        reg = &GPIO_PUP_PDN_CNTRL_REG1;
        bit_offset = (gpio - 16) * 2;  // Each GPIO uses 2 bits
    } else {
        return; // Invalid GPIO
    }
    
    // Clear the 2 bits for this GPIO (00 = no pull-up/down)
    *reg &= ~(0b11 << bit_offset);
}

void pl011_gpio() {
    // Configure GPIO14 and GPIO15 to ALT0 (function 4)
    setALT(14, 4);  // GPIO14 -> ALT0 (UART TXD)
    setALT(15, 4);  // GPIO15 -> ALT0 (UART RXD)
    
    // Disable pull-up/down for GPIO14 and GPIO15
    clearPullUpDown(14);
    clearPullUpDown(15);
    
    delay(150); // Wait for changes to take effect
    printf("PL011 UART GPIO configured\n");
}

void miniuart_gpio() {
    // Configure GPIO14 and GPIO15 to ALT5 (function 2)
    setALT(14, 2);  // GPIO14 -> ALT5 (Mini UART TXD)
    setALT(15, 2);  // GPIO15 -> ALT5 (Mini UART RXD)
    
    // Disable pull-up/down for GPIO14 and GPIO15
    clearPullUpDown(14);
    clearPullUpDown(15);
    
    delay(150);
    printf("Mini UART GPIO configured\n");
}

void spi_gpio() {
    // Configure SPI pins to ALT0 (function 4)
    setALT(8, 4);   // GPIO8  -> ALT0 (SPI CE0)
    setALT(10, 4);  // GPIO10 -> ALT0 (SPI MOSI)
    setALT(11, 4);  // GPIO11 -> ALT0 (SPI SCLK)
    
    // Disable pull-up/down for SPI pins
    clearPullUpDown(8);
    clearPullUpDown(10);
    clearPullUpDown(11);
    
    // Configure GPIO24 as output for OLED D/C pin
    setALT(24, 1);  // GPIO24 -> Output
    
    printf("SPI GPIO configured\n");
}

void oled_gpiocmd() {
    GPCLR0 = (1 << 24);  // Set GPIO24 LOW (command mode)
}

void oled_gpiodata() {
    GPSET0 = (1 << 24);  // Set GPIO24 HIGH (data mode)
}