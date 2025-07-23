#include "printf.h"
#include "utils.h"
#include "mini_uart.h"
#include "timer.h"
#include "irq.h"
#include "oled.h"

void kernel_main(void)
{
    
    uart_init();
    init_printf(0, pl011_putc);  // Hook printf to UART output
    uart_send_string("Hello, world!\r\n");
    int el = get_el();
    printf("Exception level: %d\r\n", el);  // Should now work
    
    //irq_vector_init();
	//timer_init();
	//enable_interrupt_controller();
    //enable_irq();
	//handle_timer_irq();

    while (1) {
        uart_send(uart_recv());  // Echo received UART characters
       
    }
}

//qemu-system-aarch64 -M raspi3b -kernel kernel8.img -nographic -serial mon:stdio -serial null(pl011 command for QEMU)
//qemu-system-aarch64     -M raspi3b   -kernel kernel8.img  -nographic   -serial null     -serial mon:stdio (mini uart command)
