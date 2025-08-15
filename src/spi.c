#include "printf.h"
#include "peripherals/spi.h"
#include <stdint.h>

/*initializiing clock, CS registers for standard mode*/
void spi_init(void) {
    spi_gpio(); 
    CS &= ~(3<<0);
    CLK = 250;
}

/*function to set transfer active and RX/TX */
void spi_rx_tx_transfer_active(void){

    CS |= CS_CLEAR_RX | CS_CLEAR_TX;
    CS |= CS_TA;

    printf("transfer active");
}
/*function to reset transfer to 0*/
void spi_transfer_stop(void){

    delay(100000);
    CS &= ~CS_TA;    

}

/*function to write data of 2 bytes using spi*/
void spi_write(uint8_t data) {
    DLEN = 2;

    spi_rx_tx_transfer_active();

   
    while (!(CS & CS_TXD)) {}
    FIFO = data;
    
    while (!(CS & CS_TXD)) {}
    FIFO = data;  
    printf("fifo done");
 
    while(!(CS & CS_DONE)) {
        while(CS & CS_RXD) {
            volatile uint32_t dummy = FIFO;
            (void)dummy;
        }
    }
    printf("read fifo done");

   spi_transfer_stop();

}

/*function to  read data froom fifo register*/
void spi_read(void){
    DLEN = 2;
    spi_rx_tx_transfer_active();

    while (!(CS & CS_TXD)) {}
    FIFO = 0x5678;

    while (!(CS & CS_RXD)) {}
    uint8_t data = FIFO;
    
    spi_transfer_stop();
    return data;
}
