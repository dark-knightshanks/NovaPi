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
  uart_init();
  init_printf(0, pl011_putc);
  uart_send_string("HELLO  WORLD");
  printf("hello world");

  while (1) {
    uart_send(uart_recv());
  }
}