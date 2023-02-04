#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>
#include <pic32mx.h>

#define SYS_FREQ 80000000
#define __SCALE_us (SYS_FREQ / 2000000)
#define __SCALE_ms (SYS_FREQ / 2000)

void delayMilli(uint32_t ms);
void delayMicro(uint32_t us);

#endif