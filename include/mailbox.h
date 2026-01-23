#ifndef _MAILBOX_H
#define _MAILBOX_H
#include <stdint.h>
#include <stdbool.h>
#include "peripherals/mailbox.h"



extern void mail_write(uint32_t data, int channel );
extern uint32_t mail_read(int channel);
extern uint32_t mail_framebuffer(uint32_t x, uint32_t y, uint32_t bpp);
extern void *memcpy(void *dest, const void *src, uint32_t n);

// from fontDATA.c
extern uint32_t font_get_height();
extern bool font_get_pixel(char ch, uint32_t x, uint32_t y);
extern uint32_t font_get_width();




#endif