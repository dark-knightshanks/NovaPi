#ifndef _MAILBOX_H
#define _MAILBOX_H
#include <stdint.h>

extern void mail_write(uint32_t data, int channel );
extern uint32_t mail_read(int channel);
extern uint32_t mail_framebuffer();



#endif