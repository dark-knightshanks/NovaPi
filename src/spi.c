#include "printf.h"
#include "peripherals/spi.h"
#include <stdint.h>


void spi_init(void) {
    spi_gpio(); 
    CS &= ~(3<<0);
    CLK = 250;
    CS = CS_CPHA;
    CS = CS_CPOL;

    printf("SPI initialized\n");
}

void spi_write(uint32_t data){
    DLEN = 4;
    CS |= CS_TA;
    CS |= CS_CLEAR_RX | CS_CLEAR_TX;
    
    while (CS & CS_TXD){
        FIFO = data & 0xFF;          
        FIFO = (data >> 8) & 0xFF;     
        FIFO = (data >> 16) & 0xFF;  
        FIFO = (data >> 24) & 0xFF; 

    }
    while (CS & CS_RXD){
        data = FIFO;

    }
    while(!(CS & CS_DONE)){
        while(CS & CS_RXD){
            FIFO;
        }
    }
    delay(100000);
    CS &= ~CS_TA; 
}

