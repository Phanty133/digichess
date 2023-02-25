/// @file ws2812b.h
/// @brief Driver for ws2812b LEDs

#ifndef __WS2812B_H
#define __WS2812B_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "bitops.h"
#include "delay.h"

// status led - pin 40 - F5
// prom led - pin 39 - F4
// board led - pin 38 - F6

#define LED_TRIS_CLR TRISFCLR
#define LED_PORT_SET LATFSET
#define LED_PORT_CLR LATFCLR
#define LED_PORT_INV LATFINV
#define LED_MASK (1 << 6)

// TODO: Rewrite with interrupts

// Measures out to 800ns
#define __DELAY_1_HIGH __asm__ volatile("\
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\n\
	")

#define __DELAY_1_LOW __asm__ volatile("\
		nop\n\
	")

// Measures out to 400-440ns
#define __DELAY_0_HIGH __asm__ volatile("\
		nop\nnop\nnop\nnop\nnop\nnop\nnop\n \
	")

#define __DELAY_0_LOW __asm__ volatile("\
		nop\nnop\nnop\n\
	")

// 800ns (64 cycles) High
// 450ns (36 cycles) Low
#define __WRITE_1 \
	LED_PORT_INV = LED_MASK;\
	__DELAY_1_HIGH;\
	LED_PORT_INV = LED_MASK;

// 400ns (32 cycles) High
// 850ns (68 cycles) Low
#define __WRITE_0 \
	LED_PORT_INV = LED_MASK;\
	__DELAY_0_HIGH;\
	LED_PORT_INV = LED_MASK;\
	__DELAY_0_LOW

#define __WRITE_BIT(b) if (b) { __WRITE_1; } else { __WRITE_0; }

#define ELS_PER_LED (3) // A byte per color

/// @brief Initialize pin 30 as output and set the LEDS values to 0
/// @param leds Array of 32bit integers corresponding to colors of each LED
/// @param num_leds Number of LEDs
void led_init(uint8_t* leds, int num_leds);

/// @brief Set an LED to an RGB value
/// @param leds Array of 32bit integers corresponding to colors of each LED
/// @param led LED to update
/// @param color 24bit RGB color to set the LED to
void led_set(uint8_t* leds, int led, uint32_t color);

/// @brief Display the initialized LED color values
/// @param leds Array of 32bit integers corresponding to colors of each LED
/// @param num_leds Number of LEDs
void led_display(uint8_t* leds, int num_leds);

uint32_t led_get_arr_size(uint32_t num_leds);

#endif
