/// @file buzzer.h
/// @brief Buzzer control functions

#ifndef __BUZZER_H
#define __BUZZER_H

#include <pic32mx.h>

#define BUZZER_MASK (1 << 0)

// TODO: Implement a timed buzzer function with a timer and ISR

/// @brief Initializes the buzzer pins
void buzzer_init();

/// @brief Turns on the buzzer
void buzzer_on();

/// @brief Turns off the buzzer
void buzzer_off();

#endif