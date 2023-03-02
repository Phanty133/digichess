/// @file buzzer.h
/// @brief Buzzer control functions

#ifndef __BUZZER_H
#define __BUZZER_H

#include <pic32mx.h>
#include <stdint.h>
#include "sys_defines.h"

#define BUZZER_MASK (1 << 0)

/// @brief Initializes the buzzer pins
void buzzer_init();

/// @brief Turns on the buzzer
void buzzer_on();

/// @brief Turns off the buzzer
void buzzer_off();

/// @brief Turns on a buzzer for a set period.
/// @param time_ms Time to beep for. Floored to a multiple of 100
void buzzer_timed(uint32_t time_ms);

/// @brief Should be executed every loop cycle
void buzzer_loop_update();

#endif