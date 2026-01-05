#include "peripherals/mailbox.h"
#include "printf.h"
#include "utils.h"
#include <stdint.h>

struct framebuffer fb1;

// function to read a mail form mailbox
uint32_t mail_read(int channel){

    while (1){
        if((STATUS)&(MAIL_EMPTY)){
        uint32_t data = READ;
        int ch = (data)&0xF;
        data >>= 4;
            if(ch == channel){
            return data;
            }
        }
    }
}

// function to write a mail to mailbox
void mail_write(uint32_t data, int channel ){
    while(1){
        if((STATUS)&(MAIL_FULL)){
            data <<= 4;
            data = data|channel;
            WRITE = data;   
        }
    }
}

//function for allocation of framebuffer with variable values
uint32_t mail_framebuffer() {
    fb1.width         = 800; 
    fb1.height        = 600;  
    fb1.virtual_width = 800;
    fb1.virtual_height= 600; 
    fb1.depth         = 32;  
    fb1.x_offset      = 0;
    fb1.y_offset      = 0;
    fb1.pitch         = 0;     
    fb1.frame_addr    = 0;     
    fb1.frame_size    = 0;     

    mail_write(&fb1, 1);      

    if (fb1.frame_addr == 0) {
        return 0; } 
    printf("Pitch: %u\n", fb1.pitch);
    printf("Framebuffer size: %u\n", fb1.frame_size);
    printf("Framebuffer address: 0x%x\n", fb1.frame_addr);
    return fb1.frame_addr;
}

