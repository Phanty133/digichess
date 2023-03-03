#include "game_logic.h"

extern void set_promotion_available();

static int AI_mode;
static int selected_promotion;
static int blue_turn;

// static int blue_turn;
// static int selected_promotion;
int counter = 0;
int debug1 = 0;
int debug2 = 0;
int moves[30];
ChessBoard chess_board;
MoveFlag chess_flag;
bool placed_pieces_last[GRID_ROWS][GRID_COLS];
bool placed_pieces_curr[GRID_ROWS][GRID_COLS];
int error;

int selected_piece;
int targeted_piece;

int AI_selected_piece;
int AI_targetted_piece;

void set_blue_turn(int turn) {
	blue_turn = turn;
}
int get_blue_turn() {
	return blue_turn;
}

void set_AI_mode(int mode) {
	AI_mode = mode;
}

int get_AI_mode() {
	return AI_mode;
}

void set_selected_promotion(int piece) {
	selected_promotion = piece;
}

int get_selected_promotion() {
	return selected_promotion;
}

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

void get_AI_move() {
	AI_selected_piece = 58;
	AI_targetted_piece = 57;
}

void draw_chess() {
	uint32_t color;
	if (chess_flag == STALEMATE) {
		for (int r = 0; r < GRID_ROWS; r++ ) {
			for (int c = 0; c < GRID_COLS; c++) {
				color = (get_grid_index(r, c) / 8 + get_grid_index(r, c) % 8 +counter) % 2 ? 0x080000 : 0x080808;
				
				grid_set_color(r, c, color, 0);
			}
		}
		led_display(grid_get_led_data(), GRID_LED_COUNT);
		delay_milli(300);
		counter++;
		return;
	} else if (chess_flag == WHITE_WINS) {
		for (int r = 0; r < GRID_ROWS; r++ ) {
			for (int c = 0; c < GRID_COLS; c++) {
				color = counter % 2 ? 0xffffff : 0x080808;
				
				grid_set_color(r, c, color, 1);
				delay_milli(100);
			}
		}
		counter++;
		return;
	} else if (chess_flag == BLACK_WINS) {
		for (int r = 0; r < GRID_ROWS; r++ ) {
			for (int c = 0; c < GRID_COLS; c++) {
				color = counter % 2 ? 0x080000 : 0xff0000;
				
				grid_set_color(r, c, color, 1);
				delay_milli(100);
			}
		}
		counter++;
		return;
	}

	for (int r = 0; r < GRID_ROWS; ++r ) {
		for (int c = 0; c < GRID_ROWS; ++c) {
			color = 0;
			if (is_white(chess_at_index(&chess_board, get_grid_index(r, c))))
				color = 0x080808;
			if (is_black(chess_at_index(&chess_board, get_grid_index(r, c))))
				color = 0x0a0000;
			if (get_grid_index(r, c) == selected_piece || get_grid_index(r, c) == AI_selected_piece) 
				color = error? 0xff0000 : 0xffa500;
			
			if (get_grid_index(r, c) == selected_piece && get_grid_index(r, c) == AI_selected_piece)
				color = 0x0f5a00;
			if (get_grid_index(r, c) == AI_targetted_piece) {
				color = 0xa6a804;
			}

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
				color = 0xbedead;

				grid_set_color(r, c, color, 0);
			}	
		}
	
	// if (debug1) {
	// 	grid_set_color(0, debug1, 0xaaaaaa, 0);
	// }
	// if (debug2) {
	// 	grid_set_color(1, debug2, 0x880088, 0);
	// }
	led_display(grid_get_led_data(), GRID_LED_COUNT);
}
void check_movement() {
	if (is_game_over(chess_flag))
		return;
	
	if (AI_mode != 0) {
		grid_set_color(0, 0, 0x0f000f, 1);
		delay_milli(1000);
	}

	if (AI_mode && !blue_turn) {
		uint8_t (*grid_state)[8] = (uint8_t (*)[8])grid_get_state();

		for (int r = 0; r < GRID_ROWS; r++){
			for (int c = 0; c < GRID_COLS; c++) {
				placed_pieces_curr[r][c] = grid_state[r][c];
				grid_set_color(5, 5, 0xff00ff, 1);

				if (placed_pieces_curr[r][c] == placed_pieces_last[r][c]) 
					continue;

				grid_set_color(0, 0, 0xff00ff, 1);
				delay_milli(2000); // TODO: What is this???
				
				if (selected_piece == -1 && !placed_pieces_curr[r][c]) {
					selected_piece = get_grid_index(r, c);
					error = selected_piece == AI_selected_piece;
				} else if (selected_piece == get_grid_index(r, c) && placed_pieces_curr[r][c] && targeted_piece == -1) {
					selected_piece = -1;
					error = 0;
				} else if (selected_piece != -1 && placed_pieces_curr[r][c] && get_grid_index(r, c) != AI_targetted_piece) {
					error = 1;
				} else if (get_grid_index(r, c) == AI_targetted_piece && placed_pieces_curr[r][c]) {
					chess_flag = move_piece(&chess_board, AI_selected_piece / 8, AI_selected_piece % 8,
					AI_targetted_piece / 8, AI_targetted_piece % 8);
					if (chess_flag != PROMOTION)
						selected_promotion = -1;
					blue_turn = !blue_turn;
					AI_targetted_piece = -1;
					AI_selected_piece = -1;
					selected_piece = -1;

					menu_game_change_player();
					gui_update();
				}
			}
		}

		update_placed_pieces();
		return;
	}

	uint8_t (*grid_state)[8] = (uint8_t (*)[8])grid_get_state();

	for (int r = 0; r < GRID_ROWS; r++){
		for (int c = 0; c < GRID_COLS; c++) {
			placed_pieces_curr[r][c] = grid_state[r][c];
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

				blue_turn = !blue_turn;
				menu_game_change_player();
				gui_update();

				if (AI_mode) {
					get_AI_move();
				}

				if (chess_flag) {
					selected_promotion = -1;
				}
			} else if (selected_piece != -1 && targeted_piece == -1 && !placed_pieces_curr[r][c]) {
				targeted_piece = get_grid_index(r, c);
			}
		}
	}

	update_placed_pieces();
}

void game_logic_setup() { 
	uart_write_line("Starting chess setup\n");

	arrange_board(&chess_board);

	uint8_t (*grid_state)[8] = (uint8_t (*)[8])grid_get_state();

	// place_at(&chess_board, 1, 4, wKing);
	for (int r = 0; r < GRID_ROWS; r++) {
		for(int c = 0; c < GRID_COLS; c++) {
			placed_pieces_last[r][c] = grid_state[r][c];//(chess_at_index(&chess_board, get_grid_index(r, c)) != none);
			grid_set_color(r, c, chess_at_index(&chess_board, get_grid_index(r, c)) ? 0x000008 : 0, 0); 	
		}
	}

	led_display(grid_get_led_data(), GRID_LED_COUNT);

	gui_set_menu(MENU_SPLASH);
	
	// The splash menu redirects to the mode menu by itself after 3 seconds

	AI_mode = -1;
	while (AI_mode == -1){
		gui_update();
	}

	selected_piece = -1;
	targeted_piece = -1;
	
	chess_flag = NORMAL_MOVE;
	error = 0;

	selected_promotion = -1;
	blue_turn = true;
	AI_selected_piece = AI_targetted_piece = -1;
}

void game_logic_loop() {
	check_movement();
	draw_chess();
}