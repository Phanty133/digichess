#include <pic32mx.h>
#include <stdint.h>
#include "uart.h"
#include "delay.h"
#include "sys_defines.h"

#define DEBUG_BOARD
// #define DEBUG_LCD
#define DEBUG_BUZZER
// #define DEBUG_CHESS_GAME

#ifdef DEBUG_BOARD
#include "grid.h"
#include "drivers/ws2812b/ws2812b.h"
#endif

#ifdef DEBUG_LCD
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_tests.h"
#endif

#ifdef DEBUG_BUZZER
#include "buzzer.h"
#endif

#ifdef DEBUG_CHESS_GAME
#include "chess/chess.h"
#include "grid.h"
#endif

#ifdef DEBUG_CHESS_GAME
	ChessBoard chess_board;
	bool placed_pieces_last[4][8];
	bool placed_pieces_curr[4][8];
	int error;
	int selected_piece;
	int num_pieces;
	int moves[30];
	void update_placed_pieces() {
		for (int r = 0; r < 4; ++r)
			for (int c = 0; c < 8; ++c)
				placed_pieces_last[r][c] = placed_pieces_curr[r][c];
	}
	int get_grid_index(int r, int c){
		if (r % 2)
			return 8 * r + (7-c);
		else
			return 8 * r + c;
	}

	int get_chess_index(int y, int x) {
		return y * 8 + x;
	}
#endif

void setup() {
	uart_begin(115200);

#ifdef DEBUG_BUZZER
	buzzer_init();

	buzzer_on();
	delay_milli(500);
	buzzer_off();
	delay_milli(500);
	buzzer_on();
	delay_milli(500);
	buzzer_off();
#endif
	
#ifdef DEBUG_LCD
	lcd_init();
	lcd_select();
	lcd_test_all();
#endif

#ifdef DEBUG_BOARD
	grid_init();

	TRISFCLR = GRID_POWER_MASK;
	LATFCLR = GRID_POWER_MASK;

	led_display(grid_get_led_data(), GRID_LED_COUNT);
#endif

#ifdef DEBUG_CHESS_GAME
	grid_init();
	TRISFCLR = GRID_POWER_MASK;
	LATFCLR = GRID_POWER_MASK;

	grid_reset_sensors();
	empty_board(&chess_board);
	place_at(&chess_board, 0, 4, wKing);
	place_at(&chess_board, 1, 4, wKing);
	for (int r = 0; r < 4; ++r)
		for(int c = 0; c < 8; ++c)
			placed_pieces_last[r][c] = grid_read_square(r, c);
	selected_piece = -1;
	num_pieces = 1;
	error = 0;
#endif
}

void loop() {
#ifdef DEBUG_BOARD
	grid_reset_sensors();

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 8; c++) {
			uint32_t color = !grid_read_square(r, c) ? 0x000088 : 0x80000;

			if (c == 7) {
				uart_write_num(color, 1);
			}

			grid_set_color(r, c, color, 0);
		}
	}

	led_display(grid_get_led_data(), GRID_LED_COUNT);
#endif
#ifdef DEBUG_CHESS_GAME
	grid_reset_sensors();
	uint32_t color;
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 8; c++) {
			placed_pieces_curr[r][c] = grid_read_square(r, c);
			color = 0x80000;
			if (placed_pieces_curr[r][c] != placed_pieces_last[r][c]){
				if (selected_piece == -1 && !placed_pieces_curr[r][c]) {
					selected_piece = get_grid_index(r, c);
					get_legal_moves(moves, &chess_board, r, c);
				} else if (selected_piece == get_grid_index(r, c) && placed_pieces_curr[r][c]){
					selected_piece = -1;
					moves[0] = 0;
				} else if (selected_piece != -1 && placed_pieces_curr[r][c]){
					if (move_piece(&chess_board, r, c, selected_piece / 8, selected_piece %8) < 0){
						error = 1;
						return;	
					}
				}else {
					error = 2;
					return;
				}
			}color = 0x80000;
			
		}
		for (int r = 0; r < 4; ++r )
			for (int c = 0; c < 8; ++c) {
				if (at(&chess_board, r, r % 2 ? 7-c : c) == none)
				color = 0;
			if (get_grid_index(r, c) == selected_piece) 
				color = error? 0xff0000 : 0xffa500;

			if (contains_legal_move(moves, get_grid_index(r, c)))
				color = error ? 0x0e00aa : 0x000b00;

			grid_set_color(r, c, color, 0);
			}
	
	update_placed_pieces();
	led_display(grid_get_led_data(), GRID_LED_COUNT);
#endif

}

int main() {
	setup();
	while (1) loop();

	return 0;
}
