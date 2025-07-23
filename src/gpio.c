#include "peripherals/gpio.h"
#include "utils.h"
#include "printf.h"

void miniuart_gpio(){

    unsigned int selector;

    selector = *GPFSEL1;
    selector &= ~(7<<12);                   // clean gpio14
    selector |= 2<<12;                      // set alt5 for gpio14
    selector &= ~(7<<15);                   // clean gpio15
    selector |= 2<<15;                      // set alt5 for gpio 15
    *GPFSEL1 = selector;

    // Clear pull-up/down settings for GPIO 14 and 15 (each pin uses 2 bits)
    unsigned int reg = *GPIO_PUP_PDN_CNTRL_REG0;
    reg &= ~((0b11 << (14 * 2)) | (0b11 << (15 * 2)));  // Clear bits for GPIO14 and GPIO15
    *GPIO_PUP_PDN_CNTRL_REG0 = reg;

    }

void pl011_gpio(){

        // 1. Configure GPIO14 and GPIO15 to ALT0 (UART)
        unsigned int selector = *GPFSEL1;
    
        // Clear bits for GPIO14 (bits 12-14) and GPIO15 (bits 15-17)
        selector &= ~((7 << 12) | (7 << 15));
        // Set ALT0 (100 = 4) for GPIO14 and GPIO15
        selector |= (4 << 12) | (4 << 15);
        *GPFSEL1 = selector;
    
        // 2. Disable pull-up/down for GPIO14 and GPIO15
        unsigned int reg = *GPIO_PUP_PDN_CNTRL_REG0;
        reg &= ~((0b11 << 28) | (0b11 << 30)); // clear bits
        *GPIO_PUP_PDN_CNTRL_REG0 = reg;
        delay(150);  // wait for change to latch
    
    }

void spi_gpio(){

        // clear bits for GPIO8
        unsigned int selector0 = *GPFSEL0;
        selector0 &= ~(7 << 24);
        selector0 |=  (4 << 24);// set alt0
        *GPFSEL0 = selector0;
    
        // disable pull-up/pull-down
        unsigned int reg0 = *GPIO_PUP_PDN_CNTRL_REG0;
        reg0 &= ~(0b11 << 16);
        *GPIO_PUP_PDN_CNTRL_REG0 = reg0;


        // clear bits for gpio10 and gpio11
        unsigned int selector = *GPFSEL1;
        selector &= ~((7) | (7 << 3));
        selector |= (4) | (4 << 3); // set alt0 
        *GPFSEL1 = selector;


        // 2. Disable pull-up/down for GPIO10 and GPIO11
        unsigned int reg = *GPIO_PUP_PDN_CNTRL_REG0;
        reg &= ~((0b11 << 20) | (0b11 << 22)); // clear bits
        *GPIO_PUP_PDN_CNTRL_REG0 = reg;

        // Configure GPIO24 as output
        unsigned int selector2 = *GPFSEL2;  // GPIO24 is in GPFSEL2
        selector2 &= ~(7 << 12);            // Clear bits 14:12 (GPIO24)
        selector2 |= (1 << 12);             // Set to output (001)
        *GPFSEL2 = selector2;
}

void oled_gpiocmd(){
    *GPCLR0 = (1 << 24);
}

void oled_gpiodata(){
    *GPSET0 = (1 << 24); 
}