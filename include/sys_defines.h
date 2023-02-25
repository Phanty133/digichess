/// @file sys_defines.h
/// @brief System constants

#ifndef __SYS_DEFINES_H
#define __SYS_DEFINES_H

#define SYS_FREQ (80000000)
#define PBCLK_FREQ (SYS_FREQ)

#define TIMER2CLK (80000000)
#define T2IF (1 << 8)
#define T2IE (1 << 8)
#define T2IP (2)
#define T2IS (0)

#define ENABLE_INTERRUPTS __asm__ volatile("ei");

#endif