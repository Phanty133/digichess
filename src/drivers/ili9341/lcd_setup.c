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
	// D0 - pin 8 - D10
	// D1 - pin 9 - D3
	// D2 - pin 2 - D8
	// D3 - pin 3 - D0
	// D4 - pin 4 - F1
	// D5 - pin 5 - D1
	// D6 - pin 6 - D2
	// D7 - pin 7 - D9

	// RST - A4 - B12
	// CS - A3 - B10 = CSX
	// RS - A2 - B8 = D/CX
	// WR - A1 - B4 = WRX
	// RD - A0 - B2 = RDX

	// Outputs

	// Set pins as outputs
	// Port D: 1111 1000 1111 1000
	// Port F: 1111 1111 1111 1101
	// Port B: 1110 1001 1110 1011

	lcd_init_portd();
	lcd_init_portf();
	lcd_init_portb();
}

void lcd_init_portd() {
	TRISDCLR = __LCD_PORTD_MASK;
	LATDCLR = __LCD_PORTD_MASK;
}

void lcd_init_portb() {
	TRISBCLR = __LCD_PORTB_MASK;
	uint16_t setHighMask = __LCD_RST_MASK | __LCD_CS_MASK | __LCD_RD_MASK;

	LATBCLR = __LCD_PORTB_MASK & (~setHighMask);
	LATBSET = setHighMask;
}

void lcd_init_portf() {
	TRISFCLR = __LCD_PORTF_MASK;
	LATFCLR = __LCD_PORTF_MASK;
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
