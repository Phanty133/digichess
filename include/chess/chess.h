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


/// @brief Returns index of a square with coordinates x, y
/// @param x 
/// @param y 
/// @return 
int get_index(short x, short y);

/// @brief Returns Whether given piece is white
/// @param piece 
/// @return 
bool is_white(Piece piece);
bool is_black(Piece piece);
/// @brief Returns Whether given piece is black
/// @param piece 
/// @return 

/// @brief  Returns which piece is located on the chessboard at coordinates y, x
/// @param board 
/// @param y 
/// @param x 
/// @return 
Piece at(ChessBoard *board, int y, int x);

/// @brief  Returns which piece is located on the chessboard at index 
/// @param board 
/// @param index
/// @return 
Piece chess_at_index(ChessBoard *board, int index);

/// @brief  Places a piece on the chessboard at given coordinates
/// @param board 
/// @param y 
/// @param x 
/// @param piece 
void place_at(ChessBoard *board, int y, int x, Piece piece);


/// @brief  Arranges a chessboard in a standard manner 
/// @param board 
void arrange_board(ChessBoard *board);

/// @brief Creates an empty board
/// @param board
void empty_board(ChessBoard* board);

/// @brief  Checks whether a piece of specified color would be under attack at specified coordinates
/// @param board 
/// @param y 
/// @param x 
/// @param white 
/// @return 
bool is_under_attack(ChessBoard *board, int y, int x, bool white);

/// @brief  Moves the piece on the boaD from starting coordinates to final
/// @param board 
/// @param y0 
/// @param x0 
/// @param y1 
/// @param x1 
/// @return The flag describing what kind of move was made
int move_piece(ChessBoard* board, int y0, int x0, int y1, int x1);


typedef enum MoveFlag{
	OUT_OF_BOARD,
	NOT_YOUR_TURN,
	ILLEGAL_MOVE,

	NORMAL_MOVE,
	TAKE_PIECE,
	PROMOTION,
	CASTLING,
	EN_PASSANT,

	STALEMATE,
	WHITE_WINS,
	BLACK_WINS
} MoveFlag;

/// @brief Checks whether a given flag corresponds to an illegal kind of move
/// @param flag 
/// @return 
extern bool is_illegal(MoveFlag flag);

/// @brief  Checks if a given flag corresponds to a game over
/// @param flag 
/// @return 
extern bool is_game_over(MoveFlag flag);

/// @brief  Checks if current state of the board is checkmate
/// @param board 
/// @param whites_turn 
/// @return 
bool is_checkmate(ChessBoard* board, bool whites_turn);

/// @brief  Checks if the current state of the board is stalemate
/// @param board 
/// @param whites_turn 
/// @return 
bool is_stalemate(ChessBoard* board, bool whites_turn);

/// @brief Checks whether an array of legal moves contains a specified move
/// @param legal_moves an arraay of legal moves. First element corresponds to number of moves, and corresponding elements are moves themselves
/// @param move A move being checked. Displayed as index of the target position
/// @return 
bool contains_legal_move(int* legal_moves, int move);

/// @brief Returns an allocated array with all the legal moves of a pawn of specified color at specified coordinates. 
/// The first element of the array will always contain the number of legal moves
void get_moves_pawn(int* moves, ChessBoard *board, int y, int x, bool white);

/// @brief Returns an allocated array with all the legal moves of a rook of specified color at specified coordinates. 
/// The first element of the array will always contain the number of legal moves
void get_moves_rook(int* moves, Piece board[8][8], int y, int x, bool white);

/// @brief Returns an allocated array with all the legal moves of a horse of specified color at specified coordinates. 
/// The first element of the array will always contain the number of legal moves
void get_moves_horse(int* moves, Piece board[8][8], int y, int x, bool white);

/// @brief Returns an allocated array with all the legal moves of a bishop of specified color at specified coordinates. 
/// The first element of the array will always contain the number of legal moves
void get_moves_bishop(int* moves, Piece board[8][8], int y, int x, bool white);

/// @brief Returns an allocated array with all the legal moves of a queen of specified color at specified coordinates. 
/// The first element of the array will always contain the number of legal moves
void get_moves_queen(int* moves, Piece board[8][8], int y, int x, bool white);

/// @brief Returns an allocated array with all the legal moves of a king of specified color at specified coordinates. 
/// The first element of the array will always contain the number of legal moves
void get_moves_king(int* moves, ChessBoard *board, int y, int x, bool white);

/// @brief Returns an allocated array with all the legal moves of a piece located at specified coordinates. 
/// The first element of the array will always contain the number of legal moves
void get_legal_moves(int* moves, ChessBoard *board, int y, int x);

#endif