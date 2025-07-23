#include "utils.h"
#include "peripherals/mini_uart.h"

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
    miniuart_gpio();

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