#include "utils.h"
#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"
//#include "mini_uart.h"

void muart_send ( char c )
{
	while(1) {
		if((*AUX_MU_LSR_REG)&0x20) 
			break;
	}
	*AUX_MU_IO_REG=c;
}

char muart_recv ( void )
{
	while(1) {
		if((*AUX_MU_LSR_REG)&0x01) 
			break;
	}
	return((*AUX_MU_IO_REG)&0xFF);
}

void muart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		muart_send((char)str[i]);
	}
}
void muart_init ( void )
{
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
// Rasp pi3b
//*GPPUD = 0;  // Disable pull-up/down
//delay(150);

//*GPPUDCLK0 = (1 << 14) | (1 << 15);  // Clock the control signal into GPIO 14 and 15
//delay(150);

//*GPPUDCLK0 = 0;  // Remove the clock

    *AUX_ENABLES=1;                   //Enable mini uart (this also enables access to its registers)
    *AUX_MU_CNTL_REG=0;               //Disable auto flow control and disable receiver and transmitter (for now)
    *AUX_MU_IER_REG=0;                //Disable receive and transmit interrupts
    *AUX_MU_LCR_REG=3;                //Enable 8 bit mode
    *AUX_MU_MCR_REG=0;                //Set RTS line to be always high
    *AUX_MU_BAUD_REG=270;             //Set baud rate to 115200

    *AUX_MU_CNTL_REG=3;               //Finally, enable transmitter and receiver
}
void putc ( void* p, char c)
{
	muart_send(c);
}