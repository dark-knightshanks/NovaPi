#include "peripherals/mailbox.h"
#include "printf.h"
#include "utils.h"
#include <stdint.h>
#include <stdbool.h>
#include "video.h"
#include "math.h"
#define TEXT_COLOR 0x2B2D42FF
#define BACK_COLOR 0xFFFFFFFF
#define BORDER_COLOR 0xF8F9FAFF

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
                draw_pixels(pos_x + x , pos_y + y , yes ? TEXT_COLOR : BACK_COLOR);
        }
    }
}

// Function to draw a string 
void video_draw_string(char *s, uint32_t pos_x, uint32_t pos_y){
    for (int i=0; s[i] != 0; pos_x += (font_get_width() + 2), i++) {
        video_draw_char(s[i], pos_x, pos_y);
    }
}

void video_render(uint32_t xres, uint32_t yres){
    char res[64];
    sprintf(res, "Resolution: %d x %d", xres, yres);
    uint32_t square_margin = 100;  //blue margin around red center square...

    uint64_t ms_start = timer_get_ticks();// ticks in ms before drawing on screen...
    
    for (int y=0; y<yres; y++) {
        if (y == 40) {
            //redraw the "Resolution" string since it's been overwritten by the squares...
            video_draw_string(res, 20, 20);
        }
    
        for (int x=0; x<xres; x++) {
            //bool for should be draw the red square instead of the blue margin
            bool draw_square = (y > square_margin && yres - y > square_margin) &&
                (x > square_margin && xres - x > square_margin);
            
            draw_pixels(x, y, draw_square ? 0xAA0000FF : 0x0055BBFF);
        }
    }
    
    uint64_t ms_end = timer_get_ticks();
    //ms ticks when done...
    
    sprintf(res, "Screen draw took %d ms (%d secs)", (ms_end - ms_start), (ms_end - ms_start) / 1000);
    video_draw_string(res, 20, 40);
    
    printf("DONE\n");
    
    delay(2000);
}
    
void draw_circle(uint32_t x_pos,uint32_t y_pos,uint32_t rad,uint32_t color){
    for(int y = (y_pos - rad);y <= (y_pos + rad);y++){
        for(int x = (x_pos - rad);x <= (x_pos + rad);x++){
            if(rad*rad >= (((x-x_pos)*(x-x_pos))+((y-y_pos)*(y-y_pos)))&&(y<fb1.res.height)&&(x<fb1.res.width)){
                draw_pixels(x, y, color);
            }
        }
    }   
}

void draw_rectangle(uint32_t x_pos,uint32_t y_pos,uint32_t h,uint32_t w,uint32_t color){
    uint32_t x2 = x_pos + w;
    uint32_t y2 = y_pos+ h;
    for (uint32_t y = y_pos; y < y2 && y < fb1.res.height; y++) {
        for (uint32_t x = x_pos; x < x2 && x < fb1.res.width; x++) {
            draw_pixels(x,y,color);
        }
    }
}

void ball_random_movement(uint32_t rad,uint32_t color){
    for(uint32_t y = rad; y < (fb1.res.height - rad); y+= 50){
        for(uint32_t x = rad; x < (fb1.res.width - rad); x+=(2*rad) ){
            draw_circle(x,y,rad,0x457B9DFF);
            delay(10000000);
            draw_circle(x,y,rad,color);
            
        }
    }
}

void draw_player_paddle(int x, int y, int h, int w, int color) {
    draw_rectangle(x, y, h, w, color);
}

void screen_border(uint32_t xres, uint32_t yres){
    char res[64];
    sprintf(res, "Pong game");
    uint32_t square_margin = 40; 
    for (int y=0; y<yres; y++) {
        if (y == 40) {
            video_draw_string(res, 20, 20);
        }
        for (int x=0; x<xres; x++) {
            bool draw_square = (y > square_margin && yres - y > square_margin) &&
                (x > square_margin && xres - x > square_margin);
                draw_pixels(x, y, draw_square ? 0x00000000 : BORDER_COLOR);
            if(draw_square == 1){
                ball_random_movement(10,BORDER_COLOR);
            }
            else{
                ball_random_movement(10,0x00000000);
            }
        }
}
}

void draw_game_board(uint32_t xres, uint32_t yres) {
     uint32_t border_margin = 40;
     for (int y = 0; y < yres; y++) {
         for (int x = 0; x < xres; x++) {
             bool is_inside_border = (y > border_margin && yres - y >
            border_margin) && (x > border_margin && xres - x >border_margin);

             // Draw the black play area or the colored border
            draw_pixels(x, y, is_inside_border ? 0x00000000 : 0xF8F9FAFF);
       // Using your BORDER_COLOR
        }
    }
     video_draw_string("Pong game", 20, 20);
}

 