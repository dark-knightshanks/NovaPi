#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "timer.h"
#include "i2c.h"
#include "spi.h"
#include "mailbox.h"
#include "video.h"


void kernel_main(void){
    
    muart_init();//
    init_printf(0,putc);  // Hook printf to UART output
    muart_send_string("Hello, world!\r\n");
    int el = get_el();
    printf("Exception level: %d\r\n", el);  // Should now work
 
    
    printf("MAILBOX:\n");

    printf("CORE CLOCK: %d\n", mailbox_clock_rate(CT_CORE));
    printf("EMMC CLOCK: %d\n", mailbox_clock_rate(CT_EMMC));
    printf("UART CLOCK: %d\n", mailbox_clock_rate(CT_UART));
    printf("ARM  CLOCK: %d\n", mailbox_clock_rate(CT_ARM));

    printf("I2C POWER STATE:\n");

    for (int i=0; i<3; i++) {
        bool on = mailbox_power_check(i);

        printf("POWER DOMAIN STATUS FOR %d = %d\n", i, on);
    }

    //timer_sleep(2000);

    for (int i=0; i<3; i++) {
        u32 on = 1;
        mailbox_generic_command(RPI_FIRMWARE_SET_DOMAIN_STATE, i, &on);

        printf("SET POWER DOMAIN STATUS FOR %d = %d\n", i, on);
    }

    //timer_sleep(1000);

    for (int i=0; i<3; i++) {
        bool on = mailbox_power_check(i);

        printf("POWER DOMAIN STATUS FOR %d = %d\n", i, on);
    }

    u32 max_temp = 0;

    mailbox_generic_command(RPI_FIRMWARE_GET_MAX_TEMPERATURE, 0, &max_temp);

    //Do video...
// Use more conservative resolutions first
printf("Testing 640x480\n");
video_set_resolution(640, 480, 32);

printf("Testing 1024x768\n");
video_set_resolution(1024, 768, 32);

printf("Testing 1920x1080\n");
video_set_resolution(1920, 1080, 32);

    while(1) {
        u32 cur_temp = 0;

        mailbox_generic_command(RPI_FIRMWARE_GET_TEMPERATURE, 0, &cur_temp);

        printf("Cur temp: %dC MAX: %dC\n", cur_temp / 1000, max_temp / 1000);

        timer_sleep(1000);
    }
}
    

	


//qemu-system-aarch64 -M raspi3b -kernel kernel8.img -nographic -serial mon:stdio -serial null(pl011 command for QEMU)
//qemu-system-aarch64     -M raspi3b   -kernel kernel8.img  -nographic   -serial null     -serial mon:stdio (mini uart command)
