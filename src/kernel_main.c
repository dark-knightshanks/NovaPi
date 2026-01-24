#include "printf.h"
#include "utils.h"
#include "mini_uart.h"
#include "timer.h"
#include "irq.h"
#include "spi.h"
#include "pl011.h"
#include "oled.h"
#include "peripherals/mailbox.h"
#include "mailbox.h"
#include "video.h"
#include "pong.h"

Ball game_ball;
Player player2;
Player player1;
#define  BORDER_MARGIN 40
void kernel_main(void)
{ 
    uart_init();
    init_printf(0,pl011_putc);  
    uart_send_string("Hello, world!\r\n");
    int el = get_el();
    printf("Exception level: %d\r\n", el);  

    char str[17];
    sprintf(str,"NovaPi says Hello");
    
    mail_framebuffer(1280, 720, 32);
    draw_game_board(1280,720);
    init_ball(&game_ball, 10, 0x457B9DFF); // 10 is radius, 0x457B9DFF ball color
    init_player(&player1, 50, 250, 10,30 , 0xFFFFFFFF); // Left paddle
    init_player(&player2, 1220, 250, 10, 30, 0xFFFFFFFF); // Right paddle
   
    int p1_dy = 2;
    int p2_dy = -2;

    while(1){
        
        update_ball_movement(&game_ball);
         // Move players
            move_player(&player1, p1_dy);
            move_player(&player2, p2_dy);
   
            // Simple AI to make paddles bounce
            if (player1.y <= BORDER_MARGIN || player1.y + player1.height >= 60- BORDER_MARGIN) {
                p1_dy = -p1_dy;
            }
            if (player2.y <= BORDER_MARGIN || player2.y + player2.height >= 60- BORDER_MARGIN) {
                p2_dy = -p2_dy;
          }
   

        delay(1000000);

    }

	while (1){
		//uart_send(uart_recv());
	}	
}
	