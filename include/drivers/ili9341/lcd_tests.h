/// @file lcd_tests.h
/// @brief Functions for testing LCD functionality

#ifndef __LCD_TESTS_H
#define __LCD_TESTS_H

#include <stdint.h>
#include "delay.h"
#include "drivers/ili9341/lcd_draw.h"

// Files
#include "files/images/viewsonic_8bit.bmp.h"
#include "files/images/viewsonic_4bit.bmp.h"
#include "files/images/viewsonic_1bit.bmp.h"
#include "files/fonts/ComicSansMS.ttf.h"

/// @brief LCD setup and orientation test
void lcd_setup_test();

/// @brief LCD Basic drawing function test
void lcd_draw_test();

/// @brief LCD Font rendering test
void lcd_font_test();

/// @brief LCD .bmp image rendering test
void lcd_image_test();

/// @brief Runs all LCD tests
void lcd_test_all();

#endif