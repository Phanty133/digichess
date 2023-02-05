#include "drivers/ili9341/lcd_touch.h"

static uint16_t read_adc() {
	// Start sampling, wait until converted
	AD1CON1SET = (0x1 << 1);
	while(!(AD1CON1 & (0x1 << 1)));
	while(!(AD1CON1 & 0x1));

	return ADC1BUF0;
}

/// @brief Read a number of samples from the ADC. Sample count set by __TOUCH_ADC_SAMPLES
/// @param val Pointer where to write the output value
/// @return True if the touch is definitive, False if ambiguous
static bool read_averaged_adc(uint16_t* val) {
	uint16_t samples[2];

	for (int i = 0; i < 2; i++) {
		samples[i] = read_adc();
	}

	uint16_t dSample = samples[0] - samples[1];

	if (dSample < -4 || dSample > 4) {
		return false;
	} else {
		*val = (samples[0] + samples[1]) >> 1; // Average the two samples
		return true;
	}
}

static bool read_xm(uint16_t* val) {
	AD1CHS = (8 << 16);
	return read_averaged_adc(val);
}

static bool read_yp(uint16_t* val) {
	AD1CHS = (10 << 16);
	return read_averaged_adc(val);
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

void lcd_touch_reset_pins() {
	uint16_t digitalPinMask = __TOUCH_YM_MASK + __TOUCH_XP_MASK;
	TRISDCLR = digitalPinMask;
	LATDCLR = digitalPinMask;

	uint16_t analogPinMask = __TOUCH_YP_MASK + __TOUCH_XM_MASK;
	AD1PCFGSET = analogPinMask;
	TRISBCLR = analogPinMask;
	LATBCLR = analogPinMask;
}

bool lcd_touch_read_x(uint16_t* outX) {
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
	return read_yp(outX);
}

bool lcd_touch_read_y(uint16_t* outY) {
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

	delay_micro(50); // Let voltages settle

	uint16_t outVal;
	bool isValid = read_xm(&outVal);

	if (!isValid) return false;

	*outY = 1023 - outVal;
	return true;
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

	delay_micro(50);

	uint16_t z1, z2;

	bool z1Valid = read_xm(&z1);
	bool z2Valid = read_yp(&z2);

	if (!z1Valid || !z2Valid) return 65535; // very stupid

	uint16_t x;

	if (x_val == 0) {
		bool valid = lcd_touch_read_x(&x);

		if (!valid) return 65535; // very stupid
	} else {
		x = x_val;
	}

	float rtouch = z2;
	rtouch /= z1;
	rtouch -= 1;
	rtouch *= x;
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
	uint16_t x, y;

	bool xValid = lcd_touch_read_x(&x);
	bool yValid = lcd_touch_read_y(&y);

	if (!xValid || !yValid) return false;

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
		uint16_t x, y;

		bool xValid = lcd_touch_read_x(&x);
		bool yValid = lcd_touch_read_y(&y);
		// uint16_t z = lcd_touch_read_pressure(0);
		uint16_t z = 0;

		if (!xValid || !yValid) continue;

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
