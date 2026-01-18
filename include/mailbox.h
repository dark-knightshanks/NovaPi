#ifndef _MAILBOX_H
#define _MAILBOX_H
#include <stdint.h>
#include <stdbool.h>

extern void mail_write(uint32_t data, int channel );
extern uint32_t mail_read(int channel);
extern uint32_t mail_framebuffer();
extern void draw_pixels(uint32_t x, uint16_t y, uint32_t color);
extern void video_draw_char(char c, uint32_t pos_x, uint32_t pos_y);
extern void video_draw_string(char *s, uint32_t pos_x, uint32_t pos_y);


// from fontDATA.c
extern uint32_t font_get_height();
extern bool font_get_pixel(char ch, uint32_t x, uint32_t y);
extern uint32_t font_get_width();




#endif