#include "Display.h"

// Init commands and parameters from
// https://github.com/adafruit/Adafruit_ILI9341

static const uint8_t initOptions[] = {
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

void initDisplayPins() {
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
	// RS - A2 - B8 = D/CX?
	// WR - A1 - B4 = WRX
	// RD - A0 - B2 = RDX

	// Outputs

	// Set pins as outputs
	// Port D: 1111 1000 1111 1000
	// Port F: 1111 1111 1111 1101
	// Port B: 1110 1001 1110 1011

	TRISD = 0xFFFF
		- (1 << 10)
		- (1 << 9)
		- (1 << 8)
		- (1 << 3)
		- (1 << 2)
		- (1 << 1)
		- 1;

	TRISF = 0xFFF
		- (1 << 1);
	
	TRISB = 0xFFFF
		- (1 << 12)
		- (1 << 10)
		- (1 << 8)
		- (1 << 4)
		- (1 << 2);

	// Reset outputs

	LATDCLR = 0xFFFF;
	LATFCLR = 0xFFFF;
	LATBCLR = 0xFFFF;

	LATBSET = CS_MASK + RST_MASK;
}

void selectDisplay() {
	// CS - LOW
	PORTB &= ~CS_MASK;
}

void deselectDisplay() {
	// CS - HIGH
	PORTB |= CS_MASK;
}

void setBusData(uint8_t data) {
	const int busSize = 8;
	bool bits[busSize];

	for (int i = 0; i < busSize; i++) {
		bits[i] = get_bit(data, i);
	}

	uint16_t port1 = PORTD;

	// TODO: make more efficient
	port1 = set_bit(port1, 10, bits[0]);
	port1 = set_bit(port1, 3, bits[1]);
	port1 = set_bit(port1, 8, bits[2]);
	port1 = set_bit(port1, 0, bits[3]);
	port1 = set_bit(port1, 1, bits[5]);
	port1 = set_bit(port1, 2, bits[6]);
	port1 = set_bit(port1, 9, bits[7]);

	PORTD = port1;
	PORTF = set_bit(PORTF, 1, bits[4]);
}

void pulseWrite() {
	PORTBSET = WR_MASK;
	PORTBCLR = WR_MASK;
}

void pulseRead() {
	PORTBSET = RD_MASK;
	PORTBCLR = RD_MASK;
}

void resetDisplay() {
	PORTBCLR = RST_MASK;
	PORTBSET = RST_MASK;
	delayMilli(150);
}

void writeCommand(uint8_t command) {
	// D/C - LOW
	// RD - HIGH
	PORTBSET = RD_MASK;
	PORTBCLR = DC_MASK;

	setBusData(command);
	pulseWrite();
}

void writeData(uint8_t data) {
	// D/C - HIGH
	// RD - HIGH
	PORTBSET = DC_MASK + RD_MASK;

	setBusData(data);
	pulseWrite();
}

void writeRegister(uint8_t command, uint8_t* data, uint32_t dataSize) {
	writeCommand(command);

	for (int i = 0; i < dataSize; i++) {
		writeData(data[i]);
	}
}

void readData() {
	// D/C - HIGH
	// WR - HIGH
	PORTBSET = DC_MASK + WR_MASK;
}

void sleepOut() {
	writeCommand(ILI9341_SLPOUT);
}

void displayOn() {
	writeCommand(ILI9341_DISPON);
}

// Set the options from initOptions
void setPowerSettings() {
	bool isCmd = true; // Whether the current byte is a command
	int argsLeft = 0; // How many args left
	int i = 0; // The current element in the options arr

	while (1) {
		if (isCmd) {
			uint8_t cmd = initOptions[i];

			if (cmd == 0x00) break;

			writeCommand(initOptions[i]);
			argsLeft = initOptions[++i];

			isCmd = false;
		} else {
			writeData(initOptions[i]);
			argsLeft--;
		}

		if (argsLeft == 0) isCmd = true;

		i++;
	}
}

void powerOnSequence() {
	delayMilli(20);
	resetDisplay();

	setPowerSettings();

	delayMilli(150);
	sleepOut();

	delayMilli(150);
	displayOn();
}

void setAddressWindow(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h) {
	uint16_t x1 = (x0 + w - 1);
	uint16_t y1 = (y0 + h - 1);

	// Column Address Set
	writeCommand(ILI9341_CASET);
	writeData((uint8_t)(x0 >> 8));
	writeData((uint8_t)x0);
	writeData((uint8_t)(x1 >> 8));
	writeData((uint8_t)x1);

	// Page Address Set
	writeCommand(ILI9341_PASET);
	writeData((uint8_t)(y0 >> 8));
	writeData((uint8_t)y0);
	writeData((uint8_t)(y1 >> 8));
	writeData((uint8_t)y1);
}

void initDisplay() {
	selectDisplay();
	writeCommand(0x01);
	delayMilli(100);

	powerOnSequence();
	delayMilli(150);

	writeCommand(0x38);

	int x0 = 1;
	int y0 = 1;
	int w = 238;
	int h = 318;

	setAddressWindow(x0, y0, w, h);

	writeCommand(0x2C);

	PORTBSET = DC_MASK + RD_MASK;
	setBusData(0xFF);

	for (int i = 0; i < w * h; i++) {
		pulseWrite();
		pulseWrite();
	}

	setAddressWindow(80, 160, 40, 40);

	writeCommand(0x2C);
	PORTBSET = DC_MASK + RD_MASK;

	for (int i = 0; i < 40 * 40; i++) {
		setBusData(0xF8);
		pulseWrite();

		setBusData(0x00);
		pulseWrite();
	}

	setAddressWindow(80, 120, 40, 40);

	writeCommand(0x2C);
	PORTBSET = DC_MASK + RD_MASK;

	for (int i = 0; i < 40 * 40; i++) {
		setBusData(0x07);
		pulseWrite();

		setBusData(0xE0);
		pulseWrite();
	}

	setAddressWindow(80, 80, 40, 40);

	writeCommand(0x2C);
	PORTBSET = DC_MASK + RD_MASK;

	for (int i = 0; i < 40 * 40; i++) {
		setBusData(0x00);
		pulseWrite();

		setBusData(0x1F);
		pulseWrite();
	}
}
