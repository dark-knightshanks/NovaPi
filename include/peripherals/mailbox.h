#ifndef _MAILBOX_H
#define _MAILBOX_H

#include "peripherals/base.h"
#include <stdint.h>

#define Mail_BASE (PBASE + 0xB880 )
#define MAIL_EMPTY 0x40000000
#define MAIL_FULL  0x80000000

//registers

#define READ      REG32(Mail_BASE + 0x00)
#define WRITE     REG32(Mail_BASE + 0x20)
#define STATUS    REG32(Mail_BASE + 0x18)
#define SENDER    REG32(Mail_BASE + 0x14)
#define CONFIG    REG32(Mail_BASE + 0x1c)
#define POLL      REG32(Mail_BASE + 0x10)

//channels

#define MAIL_POWER    0x0 // Mailbox Channel 0: Power Management Interface
#define MAIL_FB       0x1 // Mailbox Channel 1: Frame Buffer
#define MAIL_VUART    0x2 // Mailbox Channel 2: Virtual UART
#define MAIL_VCHIQ    0x3 // Mailbox Channel 3: VCHIQ Interface
#define MAIL_LEDS     0x4 // Mailbox Channel 4: LEDs Interface
#define MAIL_BUTTONS  0x5 // Mailbox Channel 5: Buttons Interface
#define MAIL_TOUCH    0x6 // Mailbox Channel 6: Touchscreen Interface
#define MAIL_COUNT    0x7 // Mailbox Channel 7: Counter
#define MAIL_TAGS     0x8 // Mailbox Channel 8: Tags (ARM to VC)

struct framebuffer{
    uint32_t width;          // physical framebuffer
    uint32_t height;          // physical framebuffer
    uint32_t virtual_width;         // virtual framebuffer width   
    uint32_t virtual_height;         // virtual framebuffer heigth 
    uint32_t pitch;      // pitch = width*bytes
    uint32_t depth;      // bits per pixel
    uint32_t x_offset;         // offset width
    uint32_t y_offset;         // offset heigth
    uint32_t frame_addr; // address form gpu 
    uint32_t frame_size; // size of the framebuffer = width*heigth*bytes
    };

 __attribute__((section(".mailbox_fb"), aligned(16)))
volatile struct framebuffer fb1;
    
            


#endif