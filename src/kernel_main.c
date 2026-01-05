#include "printf.h"
#include "utils.h"
#include "mini_uart.h"
#include "timer.h"
#include "irq.h"
#include "spi.h"
#include "pl011.h"
#include "oled.h"
#include "mailbox.h"


void kernel_main(void)
{ 
    muart_init();
    init_printf(0,putc);  
    muart_send_string("Hello, world!\r\n");
    int el = get_el();
    printf("Exception level: %d\r\n", el);  
    i2c_init();

    // Example: write data to a slave device (say address 0x50)
    //uint32_t slave_addr = 0x50; 
    //uint32_t data_to_send[2] = {0xAB, 0xCD}; 

    //int status = i2c_write(slave_addr, data_to_send, 2);




	while (1){
		//uart_send(uart_recv());
	}	
}
	