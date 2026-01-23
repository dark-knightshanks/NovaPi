#include "peripherals/mailbox.h"
#include "printf.h"
#include "utils.h"
#include <stdint.h>
#include <stdbool.h>
#include "mailbox.h"

static uint32_t property_data[36] __attribute__((aligned(16)));
volatile mailbox_fb_request fb1 __attribute__((aligned(16)));

void *memcpy(void *dest, const void *src, uint32_t n) {
    //simple implementation...
    uint8_t *bdest = (uint8_t *)dest;
    uint8_t *bsrc = (uint8_t *)src;

    for (int i=0; i<n; i++) {
        bdest[i] = bsrc[i];
    }

    return dest;
}

uint32_t mail_read(int channel) {
    uint32_t data;

    while (1) {
        while (STATUS & MAIL_EMPTY);   // wait until NOT empty

        data = READ;
        printf("data from read:%x\n",data);
        if ((data & 0xF) == channel) {
            printf("channel:%x\n",(data & 0xF));
            return data >> 4;
        }
    }
}

void mail_write(uint32_t data, int channel) {
    while (STATUS & MAIL_FULL);   // wait until NOT full

    WRITE = (data << 4) | channel;
}

// function for sending the mailbox request for framebuffer
/*bool mailbox_process(mailbox_tag *tags, uint32_t tags_size)
{
    printf("Mailbox process start\n");
    uint32_t total_size = tags_size + 12;

    property_data[0] = total_size;
    property_data[1] = RPI_FIRMWARE_STATUS_REQUEST;
    printf("value:%x\n",property_data[1]);

    memcpy(&property_data[2], tags, tags_size);

    property_data[(total_size / 4) - 1] = MAILBOX_TAG_LAST;

    mail_write((uint32_t)property_data, MAIL_TAGS);
    mail_read(MAIL_TAGS);
    printf("Mail sent and read\n");
    printf("value:%x\n",property_data[1]);


    if (property_data[1] != RPI_FIRMWARE_STATUS_SUCCESS)
        {
            printf("NO SUCCESS\n");
            return false;}

    memcpy(tags, &property_data[2], tags_size);

    printf("Mailbox process done\n");
    

    return true;
}*/

bool mailbox_process(mailbox_tag *tags, uint32_t tags_size)
{
    uint32_t total_size = tags_size + 8;

    property_data[0] = total_size;
    property_data[1] = RPI_FIRMWARE_STATUS_REQUEST;

    memcpy(&property_data[2], tags, tags_size);

    mail_write(((uint32_t)property_data) >> 4, MAIL_TAGS);
    mail_read(MAIL_TAGS); 

    if (property_data[1] != RPI_FIRMWARE_STATUS_SUCCESS)
        return false;

    memcpy(tags, &property_data[2], tags_size);
    return true;
}

//function for allocation of framebuffer with variable values
uint32_t mail_framebuffer(uint32_t x, uint32_t y, uint32_t bpp) {
    printf("Executing mailbox framebuffer");
    fb1.res.tag.id = MAILBOX_TAG_SET_PHYS_WH;
    fb1.res.tag.buffer_size = 8;
    fb1.res.tag.value_length = 0;
    fb1.res.width = x;
    fb1.res.height = y;
    printf("Physical res set %dx%d\n",fb1.res.width,fb1.res.height);

    fb1.vres.tag.id = MAILBOX_TAG_SET_VIRT_WH;
    fb1.vres.tag.buffer_size = 8;
    fb1.vres.tag.value_length = 0;
    fb1.vres.width = x;
    fb1.vres.height = y;
    printf("virtual res set %dx%d\n",fb1.vres.width,fb1.vres.height);

    fb1.depth.tag.id = MAILBOX_TAG_SET_DEPTH;
    fb1.depth.tag.buffer_size = 4;
    fb1.depth.tag.value_length = 0;
    fb1.depth.bpp = bpp;
    printf("Depth %d\n",fb1.depth.bpp);

    fb1.buff.tag.id = MAILBOX_TAG_ALLOCATE_BUFFER;
    fb1.buff.tag.buffer_size = 8;
    fb1.buff.tag.value_length = 0;
    fb1.buff.base = 0;
    fb1.buff.screen_size = 0;
    printf("Framebuffer address and base set\n");

    fb1.pitch.tag.id = MAILBOX_TAG_GET_PITCH;
    fb1.pitch.tag.buffer_size = 4;
    fb1.pitch.tag.value_length = 0;
    fb1.pitch.pitch = 0;
    printf("pitch set\n");

    fb1.end_tag = MAILBOX_TAG_LAST;
    
    mailbox_process((mailbox_tag *)&fb1, sizeof(fb1));   

    if (fb1.buff.base == 0) {
        printf("No address recevied\n");
        return 1; } 
    printf("Pitch: %u\n", fb1.pitch.pitch);
    printf("Resolution: %dx%d\n",fb1.res.width,fb1.res.height);
    printf("Depth: %d\n",fb1.depth.bpp);
    printf("Framebuffer size: %u\n", fb1.buff.screen_size);
    printf("Framebuffer address: 0x%x\n", fb1.buff.base);
    printf("DONE");
    return fb1.buff.base;
}


