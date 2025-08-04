#include "printf.h"
#include "utils.h"
#include "mini_uart.h"
#include "timer.h"
#include "irq.h"
#include "spi.h"
#include "pl011.h"



void kernel_main(void)
{
    
    uart_init();
    init_printf(0,pl011_putc);  // Hook printf to UART output
    uart_send_string("Hello, world!\r\n");
    int el = get_el();
    printf("Exception level: %d\r\n", el);  // Should now work
    //printf("This Eklavya project chronicles the creation of a custom OS for the Raspberry Pi 4B, complete with HDMI display support and a classic Pong game implementation. Working directly with the hardware without any underlying operating system, this project explores low-level programming, hardware interfacing, and graphics rendering. Each blog post captures the challenges, breakthroughs, and lessons learned while diving deep into ARM assembly, memory management, and peripheral control. From initial bootloader setup to rendering the first pixel on screen, this documentation serves as both a personal learning record and a resource for fellow bare-metal enthusiasts. Join me as I tackle each milestone in this ambitious journey from silicon to software, one register at a time.");
    //spi_init();
    //display_logo();
	while (1){
		uart_send(uart_recv());
	}	
}

//qemu-system-aarch64 -M raspi4b -kernel kernel8.img -nographic -serial mon:stdio -serial null(pl011 command for QEMU)
//qemu-system-aarch64     -M raspi4b   -kernel kernel8.img  -nographic   -serial null     -serial mon:stdio (mini uart command)
