#ifndef _DMA_H
#define _DMA_H

#include "peripherals/base.h"


#define DMA_BASE(channel)     (PBASE + 0x7000) + (channel*0x100)


#endif