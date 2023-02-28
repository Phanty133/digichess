#ifndef __TESTS_H
#define __TESTS_H

#include "grid.h"
#include "drivers/ws2812b/ws2812b.h"
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_tests.h"
#include "buzzer.h"
#include "chess/chess.h"
#include "grid.h"

void debug_board_setup();
void debug_board_loop();

void debug_lcd_setup();
// void debug_lcd_setup();

void debug_buzzer_setup();
// void debug_buzzer_loop();

void debug_chess_setup();
void debug_chess_loop();

#endif