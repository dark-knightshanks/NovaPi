#include "printf.h"
#include "utils.h"
#include "mini_uart.h"
#include "timer.h"
#include "irq.h"
#include "spi.h"
#include "pl011.h"


void kernel_main(void)
{
    
    muart_init();
    init_printf(0,putc);  // Hook printf to UART output
    muart_send_string("Hello, world!\r\n");
    int el = get_el();
    printf("Exception level: %d\r\n", el);  // Should now work
    spi_init();
    display_logo();
}

//qemu-system-aarch64 -M raspi3b -kernel kernel8.img -nographic -serial mon:stdio -serial null(pl011 command for QEMU)
//qemu-system-aarch64     -M raspi3b   -kernel kernel8.img  -nographic   -serial null     -serial mon:stdio (mini uart command)
