#include "drivers/ili9341/lcd_setup.h"

// Init commands and parameters from
// https://github.com/adafruit/Adafruit_ILI9341
static const uint8_t INIT_OPTIONS[] = {
	0xEF, 3, 0x03, 0x80, 0x02,
	0xCF, 3, 0x00, 0xC1, 0x30,
	0xED, 4, 0x64, 0x03, 0x12, 0x81,
	0xE8, 3, 0x85, 0x00, 0x78,
	0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
	0xF7, 1, 0x20,
	0xEA, 2, 0x00, 0x00,
	ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
	ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
	ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
	ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
	ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
	ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
	ILI9341_PIXFMT  , 1, 0x55,			   // Color format
	ILI9341_FRMCTR1 , 2, 0x00, 0x18,
	ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
	0xF2, 1, 0x00,                         // 3Gamma Function Disable
	ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
	ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
		0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
	ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
		0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
	ILI9341_SLPOUT  , 0,                // Exit Sleep
	ILI9341_DISPON  , 0,                // Display on
	0x00 // End
};

void lcd_init_pins() {
	// Data pins - Port E 0-7

	// RST - 35 - D11
	// CS - A8 - B9 = CSX
	// RS - A7 - B5 = D/CX
	// WR - 10 - D4 = WRX
	// RD - 34 - D5 = RDX

	PMCON = 0x0000; // Stop PMP module and clear register

	PMCONSET =
		(1 << 0) // PMRD strobe active high
		| (1 << 1) // PMWR strobe active high
		| (1 << 9); // Enable PMWR/PMENB port

	PMMODESET = (0b10 << 8); // Set master mode 2
	PMAEN = 0; // Disable all address and CS lines
	lcd_init_portb();
	lcd_init_portd();

	PMCONSET = 0x8000; // Enable module
}

void lcd_init_portb() {
	TRISBCLR = __LCD_PORTB_MASK;
	uint16_t setHighMask = __LCD_CS_MASK;

	LATBCLR = __LCD_PORTB_MASK & (~setHighMask);
	LATBSET = setHighMask;
}

void lcd_init_portd() {
	TRISDCLR = __LCD_RST_MASK;
	LATDSET = __LCD_RST_MASK;
}

void lcd_set_settings() {
	bool isCmd = true; // Whether the current byte is a command
	int argsLeft = 0; // How many args left
	int i = 0; // The current element in the options arr

	while (1) {
		if (isCmd) {
			uint8_t cmd = INIT_OPTIONS[i];

			if (cmd == 0x00) break;

			lcd_write_command(INIT_OPTIONS[i]);
			argsLeft = INIT_OPTIONS[++i];

			isCmd = false;
		} else {
			lcd_write_data(INIT_OPTIONS[i]);
			argsLeft--;
		}

		if (argsLeft == 0) isCmd = true;

		i++;
	}
}

void lcd_power_on() {
	delay_milli(10);
	lcd_hw_reset();

	lcd_set_settings();
	lcd_set_orientation(LCD_X_ORIENTATION, LCD_Y_ORIENTATION);
	delay_milli(120);

	lcd_sleep_off();
	delay_milli(120);

	lcd_display_on();
	delay_milli(120);
}

void lcd_init() {
	lcd_init_pins();
	lcd_select();
	lcd_power_on();
}
