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

#define __DELAY_425NS __asm__ volatile("\
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\n\
	")

#define __DELAY_100NS __asm__ volatile("\
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
	")

#define __DELAY_825NS __asm__ volatile("\
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n \
		nop\nnop\n\
	")

// 800ns (64 cycles) High
// 450ns (36 cycles) Low
#define __WRITE_1 LED_PORT_INV = LED_MASK;__DELAY_825NS;LED_PORT_INV = LED_MASK;__DELAY_425NS

// 400ns (32 cycles) High
// 850ns (68 cycles) Low
// The first HIGH delay actually uses 100ns because it doesn't work otherwise
// due to latency
#define __WRITE_0 LED_PORT_INV = LED_MASK;__DELAY_100NS;LED_PORT_INV = LED_MASK;__DELAY_825NS
#define __WRITE_BIT(b) if (b) { __WRITE_1; } else { __WRITE_0; }

/// @brief Initialize pin 30 as output and set the LEDS values to 0
/// @param leds Array of 32bit integers corresponding to colors of each LED
/// @param num_leds Number of LEDs
void led_init(uint32_t* leds, int num_leds);

/// @brief Set an LED to an RGB value
/// @param leds Array of 32bit integers corresponding to colors of each LED
/// @param led LED to update
/// @param color 24bit RGB color to set the LED to
void led_set(uint32_t* leds, int led, uint32_t color);

/// @brief Display the initialized LED color values
/// @param leds Array of 32bit integers corresponding to colors of each LED
/// @param num_leds Number of LEDs
void led_display(uint32_t* leds, int num_leds);
#endif
