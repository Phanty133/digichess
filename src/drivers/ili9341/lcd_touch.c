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

	if (dSample < -__TOUCH_SAMPLE_NOISE || dSample > __TOUCH_SAMPLE_NOISE) {
		return false;
	} else {
		*val = (samples[0] + samples[1]) >> 1; // Average the two samples
		return true;
	}
}

static bool read_xm(uint16_t* val) {
	AD1CHS = __TOUCH_XM_ADC;
	return read_averaged_adc(val);
}

bool read_yp(uint16_t* val) {
	AD1CHS = __TOUCH_YP_ADC;
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
	AD1CON3 |= (0x1 << 15);

	AD1CHSCLR = (1 << 23) | (1 << 31); // Make sure neg inputs are GND

	AD1CON1SET = (0x1 << 15); // turn on ADC	
}

void lcd_touch_reset_pins() {
	uint16_t digitalPinMask = __TOUCH_YM_MASK | __TOUCH_XP_MASK;
	TRISECLR = digitalPinMask;
	LATECLR = digitalPinMask;

	uint16_t analogPinMask = __TOUCH_YP_MASK | __TOUCH_XM_MASK;
	AD1PCFGSET = analogPinMask;
	TRISBCLR = analogPinMask;
	LATBSET = analogPinMask;
}

bool lcd_touch_read_x(uint16_t* outX) {
	// Reading X
	// Y+ : analog in
	// Y- : high-Z
	// X+ : VCC
	// X- : GND

	// Set up port D before port B to not risk sending a valid command
	// with floating control pins

	// Set port D pins (X+, Y-)
	TRISE = (TRISE | __TOUCH_YM_MASK) & (~__TOUCH_XP_MASK);

	// Pull X+ (D0) HIGH
	// To avoid a situation where the bus is 0x01, which risks a software reset
	// for god knows what reason, set the entire bus to an undefined command.
	// Seriously. Fuck this display. Never buy shit from Velleman.
	LATE |= __LCD_PORTE_MASK;

	// Set port B pins (X-, Y+)
	TRISB = (TRISB | __TOUCH_YP_MASK) & (~__TOUCH_XM_MASK);
	AD1PCFGCLR = __TOUCH_YP_MASK;

	// Pull X- LOW
	LATBCLR = __TOUCH_XM_MASK;

	delay_micro(__TOUCH_READ_DELAY); // Let voltages settle

	bool valid = read_yp(outX);

	// Reset port B immediately to minimize time for floating control pins
	AD1PCFGSET = __TOUCH_YP_MASK;
	lcd_init_portb();

	return valid;
}

bool lcd_touch_read_y(uint16_t* outY) {
	// Reading Y
	// Y+ : VCC
	// Y- : GND
	// X+ : high-Z
	// X- : analog in

	// Set up port D before port B to not risk sending a valid command
	// with floating control pins

	// Set port D pins (X+, Y-)
	TRISE = (TRISE | __TOUCH_XP_MASK) & (~__TOUCH_YM_MASK);

	// Pull Y- (D1) LOW
	// For the reasons outlined in lcd_touch_read_x(), it's better to set the
	// entire data bus to make sure we don't accidentally give the cursed display
	// a valid command.
	// LATDSET = __LCD_PORTD_MASK;
	// LATDCLR = __TOUCH_YM_MASK;
	LATE = (LATE | __LCD_PORTE_MASK) & (~__LCD_D1_MASK);

	// Set port B pins (X-, Y+)
	TRISB = (TRISB | __TOUCH_XM_MASK) & (~__TOUCH_YP_MASK);
	AD1PCFGCLR = __TOUCH_XM_MASK;

	// Pull Y+ HIGH
	LATBSET = __TOUCH_YP_MASK;
	
	delay_micro(__TOUCH_READ_DELAY); // Let voltages settle

	uint16_t outVal;
	bool isValid = read_xm(&outVal);

	// Reset port B immediately to minimize time for floating control pins
	AD1PCFGSET = __TOUCH_XM_MASK;
	lcd_init_portb();

	if (!isValid) return false;

	*outY = 1023 - outVal;
	return true;
}

uint16_t lcd_touch_read_pressure(uint16_t x_val) {
	// Pull X+ LOW
	// Pull Y- HIGH
	TRISECLR = __TOUCH_XP_MASK + __TOUCH_YM_MASK;
	LATECLR = __TOUCH_XP_MASK;
	LATESET = __TOUCH_YM_MASK;

	// X- and Y+ to inputs
	TRISBSET = __TOUCH_XM_MASK + __TOUCH_YP_MASK;
	AD1PCFGCLR = __TOUCH_XM_MASK + __TOUCH_YP_MASK;

	delay_micro(__TOUCH_READ_DELAY);

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
	uint16_t* outX,
	uint16_t* outY,
	bool resetPins
) {
	PMCONCLR = 0x8000; // Disable PMP module
	uint16_t x, y;

	bool xValid = lcd_touch_read_x(&x);
	bool yValid = lcd_touch_read_y(&y);

	PMCONSET = 0x8000; // Enable PMP module

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

	*outX = ((x - __TOUCH_X_MIN) * LCD_WIDTH) / __TOUCH_X_DELTA;
	*outY = ((y - __TOUCH_Y_MIN) * LCD_HEIGHT) / __TOUCH_Y_DELTA;

	if (resetPins) lcd_touch_reset_pins();

	return true;
}

void lcd_touch_debug_raw() {
	PMCONCLR = 0x8000; // Disable PMP module

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
		bool isTouching = lcd_touch_read_coords(&x, &y, false);

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
