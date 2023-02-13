#include "drivers/ws2812b/ws2812b.h"

void led_init(uint32_t* leds, int num_leds){
	TRISE &= 0xEF;
	for(int i = 0; i < num_leds; ++i){
		leds[i] = 0;
	}
}

void led_reset(){
	PORTE &= 0xEF;
	delay_micro(100);
}

void led_write_color(uint32_t color){
	for(int i = 1; i < 0xFF; i *= 2){
		__WRITE_BIT(i & ((color & 0x00FF00) >> 8));
	}

	for(int i = 1; i < 0xFF; i *= 2){
		__WRITE_BIT(i & ((color & 0xFF0000) >> 16));
	}
	
	for(int i = 1; i < 0xFF; i *= 2){
		__WRITE_BIT(i & (color & 0x0000FF));
	}
}

void led_set(uint32_t* leds, int led_num, uint32_t color){
	leds[led_num] = color;
}

void led_display(uint32_t* leds, int num_leds){
	LATECLR = LED_MASK;

	for(int i = 0; i < num_leds; i++) {
		led_write_color(leds[i]);
	}

	led_reset();
}