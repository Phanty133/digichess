#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "Display.h"

int main(void) {
	initDisplayPins();
	initDisplay();

	while(1);

	return 0;
}
