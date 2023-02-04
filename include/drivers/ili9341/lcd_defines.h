#ifndef __LCD_DEFINES_H
#define __LCD_DEFINES_H

#define ILI9341_TFTWIDTH 240  // ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 320 // ILI9341 max TFT height

/*
	Pin masks
	Port B
*/

#define RST_MASK (1 << 12)
#define CS_MASK (1 << 10)
#define DC_MASK (1 << 8)
#define WR_MASK (1 << 4)
#define RD_MASK (1 << 2)

/*
	ILI9341 Command IDs
*/

#define ILI9341_PWCTR1 0xC0 // Power Control 1
#define ILI9341_PWCTR2 0xC1 // Power Control 2
#define ILI9341_PWCTR3 0xC2 // Power Control 3
#define ILI9341_PWCTR4 0xC3 // Power Control 4
#define ILI9341_PWCTR5 0xC4 // Power Control 5
#define ILI9341_VMCTR1 0xC5 // VCOM Control 1
#define ILI9341_VMCTR2 0xC7 // VCOM Control 2

#define ILI9341_FRMCTR1 0xB1  // Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_VSCRDEF 0x33  // Vertical Scrolling Definition
#define ILI9341_VSCRSADD 0x37 // Vertical Scrolling Start Address

#define ILI9341_MADCTL 0x36 // Memory Access Control
#define ILI9341_PIXFMT 0x3A // COLMOD: Pixel Format Set

#define ILI9341_INVCTR 0xB4  // Display Inversion Control
#define ILI9341_DFUNCTR 0xB6 // Display Function Control

#define ILI9341_GAMMASET 0x26 // Gamma Set
#define ILI9341_GMCTRP1 0xE0  // Positive Gamma Correction
#define ILI9341_GMCTRN1 0xE1  // Negative Gamma Correction

#define ILI9341_CASET 0x2A // Column Address Set
#define ILI9341_PASET 0x2B // Page Address Set
#define ILI9341_RAMWR 0x2C // Memory Write
#define ILI9341_RAMRD 0x2E // Memory Read

#define ILI9341_DISPOFF 0x28 // Display OFF
#define ILI9341_DISPON 0x29  // Display ON

#define ILI9341_SLPIN 0x10  // Enter Sleep Mode
#define ILI9341_SLPOUT 0x11 // Sleep Out
#define ILI9341_PTLON 0x12  // Partial Mode ON
#define ILI9341_NORON 0x13  // Normal Display Mode ON
#define ILI9341_RESET 0x01  // Software reset

#endif