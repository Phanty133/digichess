#include "chess/chess.h"
#include "string.h"
#include "math.h"

void check_legal_moves_king(int* moves, ChessBoard* board, int y0, int x0, bool white);

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


void print_pos(int y, int x) {
	//printf("%c%c", x + '1', y + 'a');
}

int get_index(short y, short x) {
	return x + y * 8;
}

void add_move(int* moves, int index) {
	++moves[0];
	moves[moves[0]] = index;
}

bool is_white(Piece piece) {
	return piece < 7 && piece > 0;
}
bool is_black(Piece piece) {
	return piece >= 7 && piece < 13;
}
bool is_enemy(Piece piece1, Piece piece2) {
	return (is_white(piece1) && is_black(piece2)) || (is_white(piece2) && is_black(piece1));
}
bool is_enemy_color(bool white, Piece piece) {
	return white && is_black(piece) || !white && is_white(piece);
}
bool is_ally(Piece piece1, Piece piece2) {
	return (is_white(piece1) && is_white(piece2)) || (is_black(piece2) && is_black(piece1));
}
bool is_ally_color(bool white, Piece piece) {
	return white && is_white(piece) || !white && is_black(piece);
}
bool is_valid_place(int y, int x) {
	return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

Piece at(ChessBoard *board, int y, int x) {
	if (y >= 0 && y < 8 && x >= 0 && y < 8)
		return board->board[y][x];
	//printf("ERROR!");
}
Piece at_index(ChessBoard *board, int index) {
	int y = index / 8, x = index % 8;
	if (y >= 0 && y < 8 && x >= 0 && y < 8)
		return board->board[y][x];
	//printf("ERROR!");
}
void place_at(ChessBoard *board, int y, int x, Piece piece) {
	if (y >= 0 && y < 8 && x >= 0 && y < 8)
		board->board[y][x] = piece;
	//else
		//printf("ERROR!");
}

// Takes a 64 byte char array and places pieces on it
void arrange_board(ChessBoard* board) {
	for (int i = 0; i < 8; ++i) {
		for (int k = 0; k < 8; ++k) {
			place_at(board, i, k, none);
		}
	}

	place_at(board, 0, 0, wRook); // rooks
	place_at(board, 0, 7, wRook);
	place_at(board, 7, 0, bRook);
	place_at(board, 7, 7, bRook);

	place_at(board, 0, 1, wHorse); // horses
	place_at(board, 0, 6, wHorse);
	place_at(board, 7, 1, bHorse);
	place_at(board, 7, 6, bHorse);

	place_at(board, 0, 2, wBishop); // bishops
	place_at(board, 0, 5, wBishop);
	place_at(board, 7, 2, bBishop);
	place_at(board, 7, 5, bBishop);

	place_at(board, 0, 3, wQueen); // queens
	place_at(board, 7, 3, bQueen);

	place_at(board, 0, 4, wKing); // kings
	place_at(board, 7, 4, bKing);

	for (int i = 0; i < 8; ++i) { // Pawns
		place_at(board, 1, i, wPawn);
		place_at(board, 6, i, bPawn);
	}

	board->kingMoves[0] = board->kingMoves[1] = false; // setting flags
	for (int i = 0; i < 4; ++i) {
		board->rookMoves[i] = false;
	}
	board->lastPawnDoubleMove = false;
	board->whites_turn = true;
}
void empty_board(ChessBoard* board) {
	for (int i = 0; i < 64; ++i){
		place_at(board, i / 8, i % 8, none);
	}
	board->kingMoves[0] = board->kingMoves[1] = false; // setting flags
	for (int i = 0; i < 4; ++i) {
		board->rookMoves[i] = true;
	}
	board->lastPawnDoubleMove = false;
	board->whites_turn = true;

}

void copy_board(ChessBoard* target, ChessBoard* source) { 
	for (int i = 0; i < 64; ++i) 
		place_at(target, i / 8, i % 8, at_index(source, i));
	
	target->whites_turn = source->whites_turn;

	target->kingMoves[0] = source->kingMoves[0];
	target->kingMoves[1] = source->kingMoves[1];
	
	for(int i = 0; i < 4; ++i)
		target->rookMoves[i] = source->rookMoves[i];

	target->lastMovePawnIndex = source->lastMovePawnIndex;
	target->lastPawnDoubleMove = source->lastPawnDoubleMove;

	
}

bool contains_legal_move(int* legal_moves, int move) {
	for(int i = 1; i <= legal_moves[0]; ++i){
		if (legal_moves[i] == move)
			return true;
	}
	return false;
}

Piece select_promotion(bool white){
	// TODO promotion selection
	if (white) return wQueen;
	else return bQueen;
}

int move_piece(ChessBoard* board, int y0, int x0, int y1, int x1) {
	if (!is_valid_place(y0, x0) || !is_valid_place(y1, x1))
		return -3; // Code for an attempt at an impossible move
	if (is_white(at(board, y0, x0)) != board->whites_turn)
		return -2; // Code for an attempt to move out of turn	
	int legal_moves[30];
	get_legal_moves(legal_moves, board, y0, x0);
	if (!contains_legal_move(legal_moves, get_index(y1, x1)))
		return -1; // Code for an attempt at an illegal move
	
	int flag = 0;

	Piece moved_piece = at(board, y0, x0);
	
	
	
	if ((y1 == 7 && moved_piece == wPawn) || (y1 == 0 && moved_piece == bPawn)) {
		// Promotion
		place_at(board, y1, x1, select_promotion(is_white(moved_piece)));
		flag = 2; // Code for promotion
	} else if ((at(board, y0, x0) == (board->whites_turn ? wKing : bKing)) && x1 == x0 + 2) { 
		// Castling
		place_at(board, y1, x1 - 1, is_white(moved_piece) ? wRook : bRook);
		place_at(board, y1, x1, moved_piece);
		flag = 3; // Code for castling
	} else if ((at(board, y0, x0) == (board->whites_turn ? wKing : bKing)) && x1 == x0 -2){
		place_at(board, y1, x1 + 1, is_white(moved_piece) ? wRook : bRook);
		place_at(board, y1, x1, moved_piece);
		flag = 3; // Code for castling
	} if (x0 != x1 && moved_piece == wPawn && at(board, y1, x1) == none) {
		// en-passant
		place_at(board, y1-1, x1, none);
		place_at(board, y1, x1, moved_piece);
		flag = 4; // Code for en-passant
	} else if (x0 != x1 && moved_piece == bPawn && at(board, y1, x1) == none) {
		place_at(board, y1+1, x1, none);
		place_at(board, y1, x1, moved_piece);
		flag = 4; // Code for en-passant
	} else if (at(board, y1, x1) != none){
	//taking an enemy piece
	place_at(board, y1, x1, moved_piece);
	flag = 1; // Code for taking an enemy piece
	} else {
	// boring normal move
	place_at(board, y1, x1, moved_piece);
	flag = 0; // Code for normal move
	}

	if (at(board, y1, x1) == (board->whites_turn ? wPawn : bPawn) && absi(y1 - y0) == 2) {
		board->lastPawnDoubleMove = true;
		board->lastMovePawnIndex = get_index(y1, x1);
	} else {
		board->lastPawnDoubleMove = false;
	}

	place_at(board, y0, x0, none);
	board->whites_turn = !board->whites_turn;

	if(is_stalemate(board, board->whites_turn)) {
		flag = 5; // Code for stalemate
	} else if (is_checkmate(board, board->whites_turn)){
		flag = 6 + (int)board->whites_turn; // Code for checkmate, 7 if black wins, 6 if white wins
	}
	
	

	return flag;
}

void get_moves(int* moves, ChessBoard *board, int y, int x){
	switch (at(board, y, x)) {
	case none:
		return;
	case wPawn:
	case bPawn:
		get_moves_pawn(moves, board, y, x, is_white(at(board, y, x)));
		break;
	case wRook:
	case bRook:
		get_moves_rook(moves, board->board, y, x, is_white(at(board, y, x)));
		break;
	case wHorse:
	case bHorse:
		get_moves_horse(moves, board->board, y, x, is_white(at(board, y, x)));
		break;
	case wBishop:
	case bBishop:
		get_moves_bishop(moves, board->board, y, x, is_white(at(board, y, x)));
		break;
	case wQueen:
	case bQueen:
		get_moves_queen(moves, board->board, y, x, is_white(at(board, y, x)));
		break;
	case wKing:
	case bKing:
		get_moves_king(moves, board, y, x, is_white(at(board, y, x)));
		break;
	}
}
// Returns an allocated array with all the Legal moves. The first element of the array will always contain the number of  moves
void get_legal_moves(int* moves, ChessBoard *board, int y, int x) {
	get_moves(moves, board, y, x);
	check_legal_moves_king(moves, board, y, x, is_white(at(board, y, x)));
}

void get_moves_pawn(int* moves, ChessBoard *board, int y, int x, bool white) {
	moves[0] = 0;

	if (white) {

		if (is_valid_place(y + 1, x) && at(board, y + 1, x) == none) 
			add_move(moves, get_index(y + 1, x));
		if (is_valid_place(y + 2, x) && at(board, y + 2, x) == none)
			add_move(moves, get_index(y + 2, x));
		if (is_valid_place(y + 1, x - 1) && is_black(at(board, y + 1, x - 1)))
			add_move(moves, get_index(y + 1, x - 1));
		if (is_valid_place(y + 1, x + 1) && is_black(at(board, y + 1, x + 1)))
			add_move(moves, get_index(y + 1, x + 1));

		// en passant
		if (board->lastPawnDoubleMove && y == 4 && absi((board->lastMovePawnIndex % 8) - x) == 1 
		&& board->lastMovePawnIndex / 8 == 4) {
			add_move(moves, get_index(5, (board->lastMovePawnIndex % 8)));
		}
	}
	else{

		if (is_valid_place(y - 1, x) && at(board, y - 1, x) == none)
			add_move(moves, get_index(y - 1, x));
		if (is_valid_place(y - 2, x) && at(board, y - 2, x) == none)
		add_move(moves, get_index(y - 2, x));
		if (is_valid_place(y - 1, x - 1) && is_white(at(board, y - 1, x - 1)))
			add_move(moves, get_index(y - 1, x - 1));
		if (is_valid_place(y - 1, x + 1) && is_white(at(board, y - 1, x + 1)))
			add_move(moves, get_index(y - 1, x + 1));
		
		// en passant
		if (board->lastPawnDoubleMove && y == 3 && absi((board->lastMovePawnIndex % 8) - x) == 1 
		&& board->lastMovePawnIndex / 8 == 3) {
			add_move(moves, get_index(2, (board->lastMovePawnIndex % 8)));
		}
	}
}
void get_moves_rook(int* moves, Piece board[8][8], int y, int x, bool white) {
	moves[0] = 0;
	Piece board2[8][8];
	for(int i = 0; i < 64; ++i)
		board2[i/8][i%8] = board[i/8][i%8];
	
	for (int i = x + 1; i < 8; i++) {
		if (is_ally_color(white, board[y][i]))
			break;
		if (is_enemy_color(white, board[y][i])) {
			add_move(moves,  get_index(y, i));
			break;
		}
		add_move(moves, get_index(y, i));
	}
	for (int i = x - 1; i >= 0; i--) {
		if (is_ally_color(white, board[y][i]))
			break;
		if (is_enemy_color(white, board[y][i])) {
			add_move(moves, get_index(y, i));
			break;
		}
		
		add_move(moves, get_index(y, i));
	}

	for (int i = y + 1; i < 8; i++) {
		if (is_ally_color(white, board[i][x]))
			break;
		if (is_enemy_color(white, board[i][x])) {
			add_move(moves,  get_index(i, x));
			break;
		}
		add_move(moves, get_index(i, x));
	}
	for (int i = y - 1; i >= 0; i--) {
		if (is_ally_color(white, board[i][x]))
			break;
		if (is_enemy_color(white, board[i][x])) {
			add_move(moves, get_index(i, x));
			break;
		}
		add_move(moves, get_index(i, x));
	}
}
void get_moves_horse(int* moves, Piece board[8][8], int y, int x, bool white) {
	moves[0] = 0;

	if (is_valid_place(y - 2, x - 1) && !is_ally_color(white, board[y - 2][x - 1]))
		add_move(moves, get_index(y - 2, x - 1));
	if (is_valid_place(y - 2, x + 1) && !is_ally_color(white, board[y - 2][x + 1]))
		add_move(moves, get_index(y - 2, x + 1));
	if (is_valid_place(y + 2, x - 1) && !is_ally_color(white, board[y + 1][x - 1]))
		add_move(moves, get_index(y + 2, x - 1));
	if (is_valid_place(y + 2, x + 1) && !is_ally_color(white, board[y + 1][x + 1]))
		add_move(moves, get_index(y + 2, x + 1));

	if (is_valid_place(y - 1, x - 2) && !is_ally_color(white, board[y - 1][x - 2]))
		add_move(moves, get_index(y - 1, x - 2));
	if (is_valid_place(y - 1, x + 2) && !is_ally_color(white, board[y - 1][x + 2]))
		add_move(moves, get_index(y - 1, x + 2));
	if (is_valid_place(y + 1, x - 2) && !is_ally_color(white, board[y + 1][x - 2]))
		add_move(moves, get_index(y + 1, x - 2));
	if (is_valid_place(y + 1, x + 2) && !is_ally_color(white, board[y + 1][x + 2]))
		add_move(moves, get_index(y + 1, x + 2));

}
void get_moves_bishop(int* moves, Piece board[8][8], int y, int x, bool white) {
	moves[0] = 0;

	for (int i = 1; is_valid_place(y + i, x + i); ++i) {
		if (is_ally_color(white, board[y + i][x + i]))
			break;
		if (is_enemy_color(white, board[y + i][x + i])) {
			add_move(moves, get_index(y + i, x + i));
			break;
		}
		add_move(moves, get_index(y + i, x + i));
	}
	for (int i = 1; is_valid_place(y - i, x + i); ++i) {
		if (is_ally_color(white, board[y - i][x + i]))
			break;
		if (is_enemy_color(white, board[y - i][x + i])) {
			add_move(moves, get_index(y - i, x + i));
			break;
		}
		add_move(moves, get_index(y - i, x + i));
	}

	for (int i = 1; is_valid_place(y + i, x - i); ++i) {
		if (is_ally_color(white, board[y + i][x - i]))
			break;
		if (is_enemy_color(white, board[y + i][x - i])) {
			add_move(moves, get_index(y + i, x - i));
			break;
		}
		add_move(moves, get_index(y + i, x - i));
	}
	for (int i = 1; is_valid_place(y - i, x - i); ++i) {
		if (is_ally_color(white, board[y - i][x - i]))
			break;
		if (is_enemy_color(white, board[y - i][x - i])) {
			add_move(moves, get_index(y - i, x - i));
			break;
		}
		add_move(moves, get_index(y - i, x - i));
	}

}
void get_moves_queen(int* moves, Piece board[8][8], int y, int x, bool white) {
	moves[0] = 0;
	int moves1[30];
	int moves2[30];
	get_moves_rook(moves1, board, y, x, white);
	get_moves_bishop(moves2, board, y, x, white);

	moves[0] = moves1[0] + moves2[0];
	for (int i = 1; i <= moves1[0]; ++i)
		moves[i] = moves1[i];
	for (int i = 1; i <= moves2[0]; ++i) {
		moves[i + moves1[0]] = moves2[i];
	}

	return;
}
void get_moves_king(int* moves, ChessBoard *board, int y, int x, bool white) {
	moves[0] = 0;

	for (int i = -1; i <= 1; ++i)
		for (int k = -1; k <= 1; ++k) {
			if (is_valid_place(y + i, x + k) && !is_ally_color(white, at(board, y + i, x + k)))
				add_move(moves, get_index(y + i, x + k));
		}

	// castling
	bool att = is_under_attack(board, y, x, white);
	if (is_under_attack(board, y, x, white))
		return;
	if (white && !board->kingMoves[0]) {
		if (!board->rookMoves[0] && at(board, 0, 1) == none 
		&& at(board, 0, 2) == none && at(board, 0, 3) == none 
		&& !is_under_attack(board, 0, 1, white) && !is_under_attack(board, 0, 2, white) 
		&& !is_under_attack(board, 0, 3, white) && at(board, 0, 0) == wRook) {
			add_move(moves, get_index(0, 2));
		}
		if (!board->rookMoves[1] && at(board, 0, 6) == none 
		&& at(board, 0, 5) == none && !is_under_attack(board, 0, 6, white) 
		&& !is_under_attack(board, 0, 5, white) && at(board, 0, 7) == wRook) {
			add_move(moves, get_index(0, 6));
		}
	}
	if (!white && !board->kingMoves[1]) {
		if (!board->rookMoves[3] && at(board, 7, 1) == none && at(board, 7, 2) == none 
		&& at(board, 7, 3) == none && !is_under_attack(board, 7, 1, white) 
		&& !is_under_attack(board, 7, 2, white) 
		&& !is_under_attack(board, 7, 3, white) && at(board, 7, 0) == bRook) {
			add_move(moves, get_index(7, 2));
		}
		if (!board->rookMoves[4] && at(board, 7, 6) == none 
		&& at(board, 7, 5) == none && !is_under_attack(board, 7, 6, white) 
		&& !is_under_attack(board, 7, 5, white) && at(board, 7, 7) == bRook) {
			add_move(moves, get_index(7, 6));
		}
	}
}

bool is_under_attack(ChessBoard* board, int y, int x, bool white) {
	int pieceMoves[30];
	if (white && (is_valid_place(y + 1, x + 1) && at(board, y + 1, x + 1) == bPawn) 
	|| (is_valid_place(y + 1, x - 1) && at(board, y + 1, x - 1) == bPawn))
		return true;

	if (!white && (is_valid_place(y - 1, x + 1) && at(board, y - 1, x + 1) == wPawn)
	|| (is_valid_place(y - 1, x - 1) && at(board, y - 1, x - 1) == wPawn))
		return true;

	get_moves_horse(pieceMoves, board->board, y, x, white);

	for (int i = 1; i <= pieceMoves[0]; ++i) {
		if (white && at_index(board, pieceMoves[i]) == bHorse || !white && at_index(board, pieceMoves[i]) == wHorse)
			return true;
	}

	get_moves_rook(pieceMoves, board->board, y, x, white);

	for (int i = 1; i <= pieceMoves[0]; ++i) {
		if ((white && (at_index(board, pieceMoves[i]) == bRook || at_index(board, pieceMoves[i]) == bQueen)) ||
				(!white && (at_index(board, pieceMoves[i]) == wRook || at_index(board, pieceMoves[i]) == wQueen)))
			return true;
	}

	get_moves_bishop(pieceMoves, board->board, y, x, white);
	for (int i = 1; i <= pieceMoves[0]; ++i) {
		if (white && (at_index(board, pieceMoves[i]) == bBishop || at_index(board, pieceMoves[i]) == bQueen) ||
				!white && (at_index(board, pieceMoves[i]) == wBishop || at_index(board, pieceMoves[i]) == wQueen))
			return true;
	}

	for (int i = -1; i <= 1; ++i)
		for (int k = -1; i <= 1; ++i) {
			if (is_valid_place(y + i, x + k))
			{
				if (white && at(board, y, x) == bKing)
					return true;
				if (!white && at(board, y, x) == wKing)
					return true;
			}
		}

	return false;
}
bool is_checkmate(ChessBoard* board, bool whites_turn){
	int king_y, king_x;
	ChessBoard temp_board;
	int moves[30];
	for(int i = 0; i < 64; ++i)
		if(at_index(board, i) == (board->whites_turn ? wKing : bKing)) {
			king_y = i / 8;
			king_x = i % 8;
			break;
		}
			
	if (!is_under_attack(board, king_y, king_x, whites_turn)) return false;

	for(int i = 0; i < 64; ++i){
		if(is_ally_color(whites_turn, at_index(board, i))) {
			get_legal_moves(moves, board, i / 8, i % 8);
			if (moves[0] != 0) return false;
		}
	}
	return true;
}
bool is_stalemate(ChessBoard* board, bool whites_turn){
	int king_y, king_x;
	for(int i = 0; i < 64; ++i)
		if(at_index(board, i) == (board->whites_turn ? wKing : bKing)) {
			king_y = i / 8;
			king_x = i % 8;
			break;
		}
	if (is_under_attack(board, king_y, king_x, whites_turn))
		return false;
	
	int moves[30];
	for(int i = 0; i < 64; ++i)
		if (is_ally_color(whites_turn, at_index(board, i))) {
			get_legal_moves(moves, board, i / 8, i % 8);
			if (moves[0] != 0) return false;
		}
	return true;
}
void check_legal_moves_king(int* moves, ChessBoard* board, int y0, int x0, bool white) {
	ChessBoard temp_board;
	
	
	int temp[30];
	for (int i = 0; i <= moves[0]; ++i)
		temp[i] = moves[i];


	int checked_moves[30];
	int king_y, king_x;
	for (int i = 0; i < 64; ++i) {
		if (at(board, i / 8, i % 8) == (white ? wKing : bKing)){
			king_y = i / 8;
			king_x = i % 8;
		}
	}
	checked_moves[0] = 0;
	for(int i = 1; i <= moves[0]; ++i){
		copy_board(&temp_board, board);
		
		int y1 = moves[i] / 8;
		int x1 = moves[i] % 8;
		place_at(&temp_board, y1, x1, at(&temp_board, y0, x0));
		place_at(&temp_board, y0, x0, none);
		if (y0 == king_y && x0 == king_x ) {
			if (!is_under_attack(&temp_board, y1, x1, white))
				add_move(checked_moves, get_index(y1, x1));
		} else if (!is_under_attack(&temp_board, king_y, king_x, white))
			add_move(checked_moves, get_index(y1, x1));
	}
	for (int i = 0; i <= checked_moves[0]; ++i)
		moves[i] = checked_moves[i];
}
