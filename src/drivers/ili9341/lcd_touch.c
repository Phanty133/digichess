#include "drivers/ili9341/lcd_touch.h"

static uint16_t read_adc() {
	// Start sampling, wait until converted
	AD1CON1SET = (0x1 << 1);
	while(!(AD1CON1 & (0x1 << 1)));
	while(!(AD1CON1 & 0x1));

	return ADC1BUF0;
}

static uint16_t read_xm() {
	AD1CHS = (8 << 16);
	return read_adc();
}

static uint16_t read_yp() {
	AD1CHS = (10 << 16);
	return read_adc();
}

void lcd_touch_init() {
	// TRISDCLR = __TOUCH_YM_MASK + __TOUCH_XM_MASK;
	// AD1PCFGCLR = __TOUCH_YP_MASK + __TOUCH_XM_MASK;

	// ADC Setup

	AD1CON1CLR = (0x7 << 8); // Set FORM to 000, which is a 16-bit integer format
	AD1CON1CLR = (1 << 2); // Clear ASAM, enable manual sampling
	AD1CON1SET = (0x7 << 5); // Set autoconversion

	AD1CON2 = 0x0;
	AD1CON3SET = (0x1 << 15);

	AD1CON1SET = (0x1 << 15); // turn on ADC	
}

/// @brief Reset the pin I/O for use with the LCD
void lcd_touch_reset_pins() {
	uint16_t digitalPinMask = __TOUCH_YM_MASK + __TOUCH_XP_MASK;
	TRISDCLR = digitalPinMask;
	LATDCLR = digitalPinMask;

	uint16_t analogPinMask = __TOUCH_YP_MASK + __TOUCH_XM_MASK;
	AD1PCFGSET = analogPinMask;
	TRISBCLR = analogPinMask;
	LATBCLR = analogPinMask;
}

uint16_t lcd_touch_read_x() {
	// Set both Y pins as inputs
	TRISDSET = __TOUCH_YM_MASK;
	LATDCLR = __TOUCH_YM_MASK;

	TRISBSET = __TOUCH_YP_MASK;
	AD1PCFGCLR = __TOUCH_YP_MASK;

	// Set both X pins as outputs
	AD1PCFGSET = __TOUCH_XM_MASK;
	TRISBCLR = __TOUCH_XM_MASK;
	TRISDCLR = __TOUCH_XP_MASK;

	// Pull X+ HIGH
	LATDSET = __TOUCH_XP_MASK;

	// Pull X- LOW
	LATBCLR = __TOUCH_XM_MASK;

	delay_micro(20); // Let voltages settle

	// Read and return Y+
	return read_yp();
}

uint16_t lcd_touch_read_y() {
	// Set both X pins as inputs
	TRISDSET = __TOUCH_XP_MASK;

	TRISBSET = __TOUCH_XM_MASK;
	AD1PCFGCLR = __TOUCH_XM_MASK;

	// Set both Y pins as outputs
	AD1PCFGSET = __TOUCH_YP_MASK;
	TRISBCLR = __TOUCH_YP_MASK;
	TRISDCLR = __TOUCH_YM_MASK;

	// Pull Y+ HIGH
	LATBSET = __TOUCH_YP_MASK;

	// Pull Y- LOW
	LATDCLR = __TOUCH_YM_MASK;

	delay_micro(20); // Let voltages settle

	// Read and return X-
	return 1023 - read_xm();
}

uint16_t lcd_touch_read_pressure(uint16_t x_val) {
	// Pull X+ LOW
	// Pull Y- HIGH
	TRISDCLR = __TOUCH_XP_MASK + __TOUCH_YM_MASK;
	LATDCLR = __TOUCH_XP_MASK;
	LATDSET = __TOUCH_YM_MASK;

	// X- and Y+ to inputs
	TRISBSET = __TOUCH_XM_MASK + __TOUCH_YP_MASK;
	AD1PCFGCLR = __TOUCH_XM_MASK + __TOUCH_YP_MASK;

	delay_micro(20);

	uint16_t z1 = read_xm();
	uint16_t z2 = read_yp();

	float rtouch = z2;
	rtouch /= z1;
	rtouch -= 1;
	rtouch *= x_val == 0 ? lcd_touch_read_x() : x_val;
	rtouch *= __TOUCH_X_RESISTANCE;
	rtouch /= 1024;

	return rtouch;
}

bool lcd_touch_read_coords(
	uint16_t screenWidth,
	uint16_t screenHeight,
	uint16_t* outX,
	uint16_t* outY,
	bool resetPins
) {
	uint16_t x = lcd_touch_read_x();
	uint16_t y = lcd_touch_read_y();

	// Check if the screen is being touched
	if (
		x < __TOUCH_X_MIN || x > __TOUCH_X_MAX
		|| y < __TOUCH_Y_MIN || y > __TOUCH_Y_MAX
	) {
		if (resetPins) lcd_touch_reset_pins();
		return false;
	}

	// float x_fract = (float)(x - __TOUCH_X_MIN) / __TOUCH_X_DELTA;
	// float y_fract = (float)(y - __TOUCH_Y_MIN) / __TOUCH_Y_DELTA;

	*outX = ((x - __TOUCH_X_MIN) * screenWidth) / __TOUCH_X_DELTA;
	*outY = ((y - __TOUCH_Y_MIN) * screenHeight) / __TOUCH_Y_DELTA;

	if (resetPins) lcd_touch_reset_pins();
	return true;
}

void lcd_touch_debug_raw() {
	while(1) {
		uint16_t x = lcd_touch_read_x();
		uint16_t y = lcd_touch_read_y();
		// uint16_t z = lcd_touch_read_pressure(0);
		uint16_t z = 0;

		char buf_x[16];
		num2char(x, buf_x, 16);

		char buf_y[16];
		num2char(y, buf_y, 16);

		char buf_z[16];
		num2char(z, buf_z, 16);
		
		uart_write("X: ");
		uart_write(buf_x);
		uart_write("; Y: ");
		uart_write(buf_y);
		uart_write("; Z: ");
		uart_write_line(buf_z);

		delay_milli(100);
	}
}

void lcd_touch_debug_coords() {
	uint16_t x, y;

	while (1) {
		delay_milli(100);
		bool isTouching = lcd_touch_read_coords(240, 320, &x, &y, false);

		if (!isTouching) {
			uart_write_line("Not touching!");
			continue;
		}

		char buf_x[16];
		num2char(x, buf_x, 16);

		char buf_y[16];
		num2char(y, buf_y, 16);

		uart_write("X: ");
		uart_write(buf_x);
		uart_write("; Y: ");
		uart_write_line(buf_y);
	}
}
