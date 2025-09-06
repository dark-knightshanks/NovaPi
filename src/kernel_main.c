#include "printf.h"
#include "utils.h"
#include "mini_uart.h"
#include "timer.h"
#include "irq.h"
#include "spi.h"
#include "pl011.h"
#include "oled.h"


void kernel_main(void)
{ 
    muart_init();
    init_printf(0,putc);  
    muart_send_string("Hello, world!\r\n");
    int el = get_el();
    printf("Exception level: %d\r\n", el);  
    
    spi_init();
    spi_write(0x96);


	while (1){
		//uart_send(uart_recv());
	}	
}
	