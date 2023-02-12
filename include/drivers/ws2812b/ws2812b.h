/// @file ws2817b.h
/// @brief driver for ws2812b LEDs

#ifndef __WS2812B_H
#define __WS2812B_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "bitops.h"
#include "delay.h"

/// @brief  initialize pin 30 as output and set the LEDS values to 0
/// @param leds array of 32bit integers corresponding to colors of each LED
/// @param num_leds number of LEDs
void led_init(uint32_t* leds, int num_leds);

/// @brief set an LED to an RGB value
/// @param data Data byte
void led_set(uint32_t* leds, int ledNum, uint32_t color);


/// @brief display the initialized LED color values
/// @param leds array of 32bit integers corresponding to colors of each LED
/// @param num_leds number of LEDs
void led_display(uint32_t* leds, int num_leds);
#endif
