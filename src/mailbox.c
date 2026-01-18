#include "peripherals/mailbox.h"
#include "printf.h"
#include "utils.h"
#include <stdint.h>
#include <stdbool.h>

#define TEXT_COLOR 0xFFFFFFFF
#define BACK_COLOR 0x0055BBFF


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
void mail_write(uint32_t data, int channel){
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

// Function to manipulate pixels 
void draw_pixels(uint32_t x, uint16_t y, uint32_t color){
    //Convert  ARM address form gpu address
    volatile uint8_t *frame_buffer = (uint8_t *)(fb1.frame_addr & 0x3FFFFFFF);

    uint32_t bytes_per_pixel = fb1.depth / 8;

    uint32_t pixel_offset = (y * fb1.pitch) + (x * bytes_per_pixel);
     
    
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8)  & 0xFF;
    uint8_t a = color & 0xFF;

    if (fb1.depth == 32) {
        // Write bytes in little-endian B G R A order
        frame_buffer[pixel_offset++] = b;
        frame_buffer[pixel_offset++] = g;
        frame_buffer[pixel_offset++] = r;
        frame_buffer[pixel_offset++] = a;
    } else if (fb1.depth == 16) {
        // Convert 32-bit color to RGB565
        uint16_t color16 = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
        frame_buffer[pixel_offset++] = color16 & 0xFF;
        frame_buffer[pixel_offset++] = (color16 >> 8) & 0xFF;
    }

}

// Function to draw a single character
void video_draw_char(char c, uint32_t pos_x, uint32_t pos_y){
    for (int y=0; y<font_get_height(); y++) {
        for (int x=0; x<font_get_width(); x++) {
            bool yes = font_get_pixel(c, x, y); //gets whether there is a pixel for the font at this pos...
            video_draw_pixel(pos_x + x, pos_y + y, yes ? TEXT_COLOR : BACK_COLOR);
        }
    }
}

// Function to draw a string 
void video_draw_string(char *s, uint32_t pos_x, uint32_t pos_y){
    for (int i=0; s[i] != 0; pos_x += (font_get_width() + 2), i++) {
        video_draw_char(s[i], pos_x, pos_y);
    }
}


