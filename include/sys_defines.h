/// @file sys_defines.h
/// @brief System constants

#ifndef __SYS_DEFINES_H
#define __SYS_DEFINES_H

#define SYS_FREQ (80000000)
#define PBCLK_FREQ (SYS_FREQ)

#define TIMER2CLK (80000000)
#define T2IF (1 << 8)
#define T2IE (1 << 8)

#define TIMER3CLK (80000000)
#define T3IF (1 << 12)
#define T3IE (1 << 12)

#define TIMER4CLK (80000000)
#define T4IF (1 << 16)
#define T4IE (1 << 16)

#define TIMER5CLK (80000000)
#define T5IF (1 << 20)
#define T5IE (1 << 20)

#define ENABLE_INTERRUPTS __asm__ volatile("ei");

#endif