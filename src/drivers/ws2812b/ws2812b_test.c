#include "drivers/ws2812b/ws2812b_test.h"

void led_test() {
	int num_leds = 24;
	uint32_t leds[num_leds];
	led_init(leds, num_leds);
	int counter = 0;

	// while(1){
	// 	led_set(leds, counter, 0x0000FF);
		
	// 	if (counter == 0) {
	// 		led_set(leds, num_leds - 1, 0);
	// 	} else {
	// 		led_set(leds, counter - 1, 0);
	// 	}

	// 	counter = (counter + 1) % num_leds;
	// 	led_display(leds, num_leds);

	// 	delay_milli(20);
	// }

	for (int i = 0; i < num_leds; i++) {
		led_set(leds, i, 0x888800);
	}

	led_display(leds, num_leds);
}