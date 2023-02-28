#include <pic32mx.h>
#include <stdint.h>
#include "uart.h"
#include "delay.h"
#include "sys_defines.h"
#include "tests.h"

// #define DEBUG_BOARD
// #define DEBUG_LCD
// #define DEBUG_BUZZER
#define DEBUG_CHESS_GAME

#ifdef DEBUG_CHESS_GAME
#include "chess/chess.h"
#include "grid.h"
#endif

#ifdef DEBUG_CHESS_GAME
	int counter = 0;
	
	int debug1 = 0;
	int debug2 = 0;

	ChessBoard chess_board;
	MoveFlag chess_flag;
	bool placed_pieces_last[GRID_ROWS][GRID_COLS];
	bool placed_pieces_curr[GRID_ROWS][GRID_COLS];
	int error;
	int selected_piece;
	int targeted_piece;
	int rook_place_position;
	int num_pieces;
	int moves[30];
	void update_placed_pieces() {
		for (int r = 0; r < GRID_ROWS; ++r)
			for (int c = 0; c < GRID_COLS; ++c)
				placed_pieces_last[r][c] = placed_pieces_curr[r][c];
	}
	int get_grid_index(int r, int c) {
		return r + GRID_ROWS * ((r % 2) ? ((GRID_COLS - 1 - c)) : (c));
	}

	int get_chess_index(int y, int x) {
		return y * 8 + x;
	}
#endif

void setup() {
	uart_begin(115200);

#ifdef DEBUG_BUZZER
	debug_buzzer_setup();
#endif
	
#ifdef DEBUG_LCD
	debug_lcd_setup();
#endif

#ifdef DEBUG_BOARD
	debug_board_setup();
#endif

#ifdef DEBUG_CHESS_GAME
	grid_init();
	TRISFCLR = GRID_POWER_MASK;
	LATFCLR = GRID_POWER_MASK;

	grid_reset_sensors();
	empty_board(&chess_board);
	place_at(&chess_board, 0, 4, wKing);
	place_at(&chess_board, 3, 0, bPawn);
	place_at(&chess_board, 1, 1, wPawn);
	place_at(&chess_board, 7, 4, bKing);
	chess_board.whites_turn = true;
	chess_board.rookMoves[0] = false;
	chess_board.rookMoves[1] = false;
	chess_board.rookMoves[2] = false;
	chess_board.rookMoves[3] = false;
	// place_at(&chess_board, 1, 4, wKing);
	for (int r = 0; r < GRID_ROWS; r++) {
		for(int c = 0; c < GRID_COLS; c++) {
			placed_pieces_last[r][c] = !grid_read_square(r, c);//(chess_at_index(&chess_board, get_grid_index(r, c)) != none);
			grid_set_color(r, c, chess_at_index(&chess_board, get_grid_index(r, c)) ? 0x000008 : 0, 0); 	
		}
	}

	led_display(grid_get_led_data(), GRID_LED_COUNT);
	selected_piece = -1;
	targeted_piece = -1;
	rook_place_position = -1;
	chess_flag = NORMAL_MOVE;
	error = 0;
#endif
}

void loop() {
#ifdef DEBUG_BOARD
	debug_board_loop();
#endif

#ifdef DEBUG_CHESS_GAME
	uint32_t color;
	if (chess_flag == STALEMATE) {
		for (int r = 0; r < GRID_ROWS; r++ )
			for (int c = 0; c < GRID_COLS; c++) {
				color = (get_grid_index(r, c) / 8 + get_grid_index(r, c) % 8 +counter) % 2 ? 0x080000 : 0x080808;
				
				grid_set_color(r, c, color, 0);
			}
		led_display(grid_get_led_data(), GRID_LED_COUNT);
		delay_milli(300);
		counter++;
		return;
	} else if (chess_flag == WHITE_WINS) {
		for (int r = 0; r < GRID_ROWS; r++ )
			for (int c = 0; c < GRID_COLS; c++) {
				color = counter % 2 ? 0xffffff : 0x080808;
				
				grid_set_color(r, c, color, 1);
				delay_milli(100);
			}
		
		counter++;
		return;
	} else if (chess_flag == BLACK_WINS) {
		for (int r = 0; r < GRID_ROWS; r++ )
			for (int c = 0; c < GRID_COLS; c++) {
				color = counter % 2 ? 0x080000 : 0xff0000;
				
				grid_set_color(r, c, color, 1);
				delay_milli(100);
			}
		
		counter++;
		return;
	}

	grid_reset_sensors();
	
	for (int r = 0; r < GRID_ROWS; r++)
		for (int c = 0; c < GRID_COLS; c++) {
			placed_pieces_curr[r][c] = !grid_read_square(r, c);
			if (placed_pieces_curr[r][c] == placed_pieces_last[r][c]) 
				continue;

			// if (placed_pieces_curr[r][c] && rook_place_position == get_grid_index(r, c)) {
			// 	rook_place_position = -1;
			// 	targeted_piece = -1;
			// } 
			else if (selected_piece == -1 && !placed_pieces_curr[r][c]) {
				selected_piece = get_grid_index(r, c);
				get_legal_moves(moves, &chess_board, get_grid_index(r, c) / 8, get_grid_index(r, c) % 8);
			} else if (selected_piece == get_grid_index(r, c) && placed_pieces_curr[r][c] && targeted_piece == -1) {
				selected_piece = -1;
				moves[0] = 0;
				error = 0;
			} else if (selected_piece != -1 && placed_pieces_curr[r][c]) {
				chess_flag = move_piece(&chess_board, selected_piece / 8, selected_piece %8, get_grid_index(r, c) / 8, get_grid_index(r, c) % 8);
				if (is_illegal(chess_flag) ) {
					error = 1;
					return;	
				} else if (targeted_piece == get_grid_index(r, c)) {
					targeted_piece = -1;
					selected_piece = -1;
					moves[0] = 0;
				} else if(chess_flag == CASTLING && get_grid_index(r, c) % 8 == 2 && targeted_piece % 8 == 0) { // Castling
					selected_piece = -1;
					// debug1 = 1;
					targeted_piece = -1;
					moves[0] = 0;
				} else if(chess_flag == CASTLING && get_grid_index(r, c) % 8 == 6 && targeted_piece % 8 == 7) {
					selected_piece = -1;
					targeted_piece = -1;
					moves[0] = 0;
				} else if (chess_flag == EN_PASSANT && targeted_piece == get_grid_index(r, c) - 8 || targeted_piece == get_grid_index(r, c) + 8) {
					targeted_piece = -1;
					selected_piece = -1;
					moves[0] = 0;
				} else if (targeted_piece != -1 && targeted_piece != get_grid_index(r, c)) {
					selected_piece = targeted_piece;
					get_legal_moves(moves, &chess_board, get_grid_index(r, c) / 8, get_grid_index(r, c) % 8);
					targeted_piece = -1;
				} else{
					selected_piece = -1;
					moves[0] = 0;
				}
				// if (targeted_piece != -1) debug1 = 3;
				// else debug1 = 0;
			} else if (selected_piece != -1 && targeted_piece == -1 && !placed_pieces_curr[r][c]) {
				targeted_piece = get_grid_index(r, c);
			}
		}
		
	// if (selected_piece != -1 && moves[0] == 0) { //DEBUG
	// 	debug1 = 1;
	// }
	
	
	for (int r = 0; r < GRID_ROWS; ++r )
		for (int c = 0; c < GRID_ROWS; ++c) {
			color = 0;
			if (is_white(chess_at_index(&chess_board, get_grid_index(r, c))))
				color = 0x080808;
			if (is_black(chess_at_index(&chess_board, get_grid_index(r, c))))
				color = 0x0a0000;
		if (get_grid_index(r, c) == selected_piece) 
			color = error? 0xff0000 : 0xffa500;

		if (contains_legal_move(moves, get_grid_index(r, c))){
			if (chess_at_index(&chess_board, selected_piece) == wPawn && chess_at_index(&chess_board, get_grid_index(r, c) - 8) == bPawn 
			&& chess_at_index(&chess_board, get_grid_index(r, c)) == none)
				color = 0x100010;
			else if (chess_at_index(&chess_board, selected_piece) == bPawn && chess_at_index(&chess_board, get_grid_index(r, c) + 8) == wPawn 
			&& chess_at_index(&chess_board, get_grid_index(r, c)) == none)
				color = 0x100010;
			else
				color = chess_at_index(&chess_board, get_grid_index(r, c)) != none ? 0x0e00aa : 0x000b00;
		}
		if (get_grid_index(r, c) == targeted_piece)
			color = 0xffffff;

			grid_set_color(r, c, color, 0);
		}
	
	// if (debug1) {
	// 	grid_set_color(0, debug1, 0xaaaaaa, 0);
	// }
	// if (debug2) {
	// 	grid_set_color(1, debug2, 0x880088, 0);
	// }
	update_placed_pieces();
	led_display(grid_get_led_data(), GRID_LED_COUNT);
#endif

}

int main() {
	setup();
	while (1) loop();

	return 0;
}
