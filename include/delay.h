#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>
#include <pic32mx.h>
#include "sys_defines.h"

#define __SCALE_us (SYS_FREQ / 2000000)
#define __SCALE_ms (SYS_FREQ / 2000)

void delay_milli(uint32_t ms);
void delay_micro(uint32_t us);

#endif