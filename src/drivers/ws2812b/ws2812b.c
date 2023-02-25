#include "drivers/ws2812b/ws2812b.h"

void led_init(uint8_t* leds, int num_leds){
	LED_TRIS_CLR = LED_MASK;
	
	for(int i = 0; i < led_get_arr_size(num_leds); ++i){
		leds[i] = 0;
	}
}

void led_reset(){
	LED_PORT_CLR = LED_MASK;
	delay_micro(100);
}

void led_set(uint8_t* leds, int led_num, uint32_t color){
	uint8_t r = ((color & 0xFF0000) >> 16);
	uint8_t g = ((color & 0x00FF00) >> 8);
	uint8_t b = (color & 0x0000FF);

	int start = led_num * ELS_PER_LED;

	for (int i = 0; i < 8; i++) {
		leds[start + i] = get_bit(g, 7 - i);
	}

	for (int i = 0; i < 8; i++) {
		leds[start + i + 8] = get_bit(r, 7 - i);
	}

	for (int i = 0; i < 8; i++) {
		leds[start + i + 16] = get_bit(b, 7 - i);
	}
}

void led_display(uint8_t* leds, int num_leds){
	LED_PORT_CLR = LED_MASK;
	uint32_t arr_size = led_get_arr_size(num_leds);

	for (int i = 0; i < arr_size; i++) {
		__WRITE_BIT(leds[i]);
	}

	led_reset();
}

uint32_t led_get_arr_size(uint32_t num_leds) {
	return num_leds * ELS_PER_LED;
}
