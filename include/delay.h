/// @file delay.h
/// @brief Delay functions

#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>
#include <pic32mx.h>
#include "sys_defines.h"

#define __SCALE_ns (SYS_FREQ / 20000000)
#define __SCALE_us (SYS_FREQ / 2000000)
#define __SCALE_ms (SYS_FREQ / 2000)


/// @brief Stalls the processor for some amount of time
/// @param ms Delay time in milliseconds
void delay_milli(uint32_t ms);

/// @brief Stalls the processor for some amount of time
/// @param us Delay time in microseconds
void delay_micro(uint32_t us);

#endif