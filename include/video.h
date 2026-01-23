#ifndef _VIDEO_H
#define _VIDEO_H


#include <stdint.h>
#include <stdbool.h>
#include "peripherals/mailbox.h"


extern void draw_pixels(uint32_t x, uint16_t y, uint32_t color);
extern void video_draw_char(char c, uint32_t pos_x, uint32_t pos_y);
extern void video_draw_string(char *s, uint32_t pos_x, uint32_t pos_y);

#endif