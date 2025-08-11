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
  test_spi_pattern(); // Use this first to verify SPI timing
    //display_logo();
    

while (1) {
  uart_send(uart_recv()); // UART echo
}
}


//qemu-system-aarch64 -M raspi4b -kernel kernel8.img -nographic -serial mon:stdio -serial null(pl011 command for QEMU)
//qemu-system-aarch64     -M raspi4b   -kernel kernel8.img  -nographic   -serial null     -serial mon:stdio (mini uart command)
