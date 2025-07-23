#ifndef OLED_H
#define OLED_H

#include <stdio.h>
#include <string.h>

#define SRA_LOGO 1
extern void init_oled();
extern void display_logo(int logo_id);

#endif