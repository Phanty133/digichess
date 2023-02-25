#ifndef __CHESS_H
#define __CHESS_H

#include <stdbool.h>

typedef enum Piece{
    none,

    wPawn,
    wRook,
    wHorse,
    wBishop,
    wQueen,
    wKing,
    
    bPawn,
    bRook,
    bHorse,
    bBishop,
    bQueen,
    bKing,

    mark
} Piece;

typedef struct ChessBoard {
    Piece board[8][8];
    bool rookMoves[4]; // shows if pice has been moved 0 and 1 correspond to white rooks at 1a and 1h, 2 and 3 - black rooks 7a and 7h
    bool kingMoves[2]; // shows if pice has been moved 0 for white king, 1 for black king
    bool lastPawnDoubleMove; // 1 if in last move a pawn move forward 2 squares
    int lastMovePawnIndex; // index of a pawn that moved 2 squares last move for (en passant)
		bool whites_turn;
} ChessBoard;

void swap(int *a, int *b);


void print_pos(int y, int x);

int get_index(short x, short y);

bool is_white(Piece piece);
bool is_black(Piece piece);

Piece at(ChessBoard *board, int y, int x);
void place_at(ChessBoard *board, int y, int x, Piece piece);


//Takes a 64 Piece array and places pieces on it
void arrange_board(ChessBoard *board);

// Creates an empty board
void empty_board(ChessBoard* board);

bool is_under_attack(ChessBoard *board, int y, int x, bool white);

int move_piece(ChessBoard* board, int y0, int x0, int y1, int x1);

bool is_checkmate(ChessBoard* board, bool whites_turn);
bool is_stalemate(ChessBoard* board, bool whites_turn);
//Returns an allocated array with all the legal moves. The first element of the array will always contain the number of legal moves
void get_moves_pawn(int* moves, ChessBoard *board, int y, int x, bool white);
void get_moves_rook(int* moves, Piece board[8][8], int y, int x, bool white);
void get_moves_horse(int* moves, Piece board[8][8], int y, int x, bool white);
void get_moves_bishop(int* moves, Piece board[8][8], int y, int x, bool white);
void get_moves_queen(int* moves, Piece board[8][8], int y, int x, bool white);
void get_moves_king(int* moves, ChessBoard *board, int y, int x, bool white);

void get_legal_moves(int* moves, ChessBoard *board, int y, int x);

#endif