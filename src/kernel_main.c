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
spi_init();
spi_write(0x12345678);

while (1) {
  uart_send(uart_recv()); // UART echo
}
}


//qemu-system-aarch64 -M raspi4b -kernel kernel8.img -nographic -serial mon:stdio -serial null(pl011 command for QEMU)
//qemu-system-aarch64     -M raspi4b   -kernel kernel8.img  -nographic   -serial null     -serial mon:stdio (mini uart command)
