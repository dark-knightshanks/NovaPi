#include "peripherals/mailbox.h"
#include "printf.h"
#include "utils.h"
#include <stdint.h>
#include <stdbool.h>
#include "video.h"
#define TEXT_COLOR 0xFFFFFFFF
#define BACK_COLOR 0x0055BBFF

extern volatile mailbox_fb_request fb1;

// Function to manipulate pixels 
void draw_pixels(uint32_t x, uint16_t y, uint32_t color){

    if (x >= fb1.res.width || y >= fb1.res.height) return;
    //Convert  ARM address form gpu address
    volatile uint8_t *frame_buffer = (uint8_t *)(fb1.buff.base & 0x3FFFFFFF);

    uint32_t bytes_per_pixel = fb1.depth.bpp / 8;

    uint32_t pixel_offset = (y * fb1.pitch.pitch) + (x * bytes_per_pixel);
     
    
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8)  & 0xFF;
    uint8_t a = color & 0xFF;

    // Write bytes in little-endian B G R A order
    frame_buffer[pixel_offset++] = b;
    frame_buffer[pixel_offset++] = g;
    frame_buffer[pixel_offset++] = r;
    frame_buffer[pixel_offset++] = a;
}

// Function to draw a single character
void video_draw_char(char c, uint32_t pos_x, uint32_t pos_y){
    for (int y=0; y<font_get_height(); y++) {
        for (int x=0; x<font_get_width(); x++) {
            bool yes = font_get_pixel(c, x, y); //gets whether there is a pixel for the font at this pos...
                draw_pixels(pos_x + x, pos_y + y, yes ? TEXT_COLOR : BACK_COLOR);
        }
    }
}

// Function to draw a string 
void video_draw_string(char *s, uint32_t pos_x, uint32_t pos_y){
    for (int i=0; s[i] != 0; pos_x += (font_get_width() + 2), i++) {
        video_draw_char(s[i], pos_x, pos_y);
    }
}
