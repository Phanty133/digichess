/// @file game_logic.h
/// @brief the final logic of the game

#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#include "chess/chess.h"
#include "grid.h"
#include "gui/gui.h"
#include "uart.h"
#include "gui/menus/menu_game.h"

void set_AI_mode(int mode);
int get_AI_mode();

void set_selected_promotion(int piece);
int get_selected_promotion();

void set_blue_turn(int turn);
int get_blue_turn();

/// @brief Sets up the main game logic
void game_logic_setup();
/// @brief Performed in each frame of the game
void game_logic_loop();

/// @brief Updates value of previusly set pieces to current pieces for next iteration
void update_placed_pieces();

/// @brief returns chess logic index from position of the grid
/// @param r row
/// @param c column't
/// @return chess logic index
int get_grid_index(int r, int c);

/// @brief Returns chess logic index
/// @param y y coordinate on chessboard
/// @param x x coordinate on chessboard
/// @return index of the piece
int get_chess_index(int y, int x);

/// @brief Fetches moves from Stockfish
void get_AI_move();

/// @brief Displays current situation of the game on the board 
void draw_chess();
/// @brief Analyzes movement of pieces on the board
void check_movement();
#endif