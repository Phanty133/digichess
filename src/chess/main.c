#include <stdio.h>
#include "chess.h"
#include <stdlib.h>

void print_moves(Piece board[8][8], int *moves);
void print_moves_numerical(int *moves);
void print_board(Piece board[8][8]);

int main() {
	ChessBoard board;
	int moves[30];
	arrange_board(&board);
	int y0, x0, y1, x1, flag;



	while (true) {
		printf("\n==============================================\n");
		print_board(board.board);
		printf("\n%s\'s turn. Enter the move: ", board.whites_turn ? "White" : "Black");
		scanf("%d%d%d%d", &y0, &x0, &y1, &x1);
		flag = move_piece(&board, y0, x0, y1, x1);
		if (flag < 0) {
			printf("You can\'t make that move");
		} else if (flag == 4) {
			printf("\nSTALEMATE!\n");
			break;
		} else if (flag == 5) {
			printf("\nWhite Wins!\n");
			break;
		} else if (flag == 6) {
			printf("\nBlack Wins!\n");
			break;
		}
	}
}

void print_moves(Piece board[8][8], int *moves) {
	Piece tempBoard[8][8];
	for (int i = 0; i < 8; ++i) {
		for (int k = 0; k < 8; ++k) {
			tempBoard[i][k] = board[i][k];
		}
	}
	for (int i = 1; i <= moves[0]; ++i) {
		tempBoard[moves[i] / 8][moves[i] % 8] = mark;
	}
	print_board(tempBoard);
	free(moves);
}

// prints out a board
void print_board(Piece board[8][8]) {
	for (int y = 7; y >= 0; --y) {
		for (int x = 0; x < 8; ++x) {
			switch (board[y][x]) {
			case none:
				printf("\033[0;37m.\033[0m");
				break;
			case wPawn:
				printf("\033[0;37mp\033[0m");
				break;
			case bPawn:
				printf("\033[0;31mp\033[0m");
				break;
			case wRook:
				printf("\033[0;37mr\033[0m");
				break;
			case bRook:
				printf("\033[0;31mr\033[0m");
				break;
			case wHorse:
				printf("\033[0;37mh\033[0m");
				break;
			case bHorse:
				printf("\033[0;31mh\033[0m");
				break;
			case wBishop:
				printf("\033[0;37mb\033[0m");
				break;
			case bBishop:
				printf("\033[0;31mb\033[0m");
				break;
			case wQueen:
				printf("\033[0;37mQ\033[0m");
				break;
			case bQueen:
				printf("\033[0;31mQ\033[0m");
				break;
			case wKing:
				printf("\033[0;37mK\033[0m");
				break;
			case bKing:
				printf("\033[0;31mK\033[0m");
				break;
			case mark:
				putchar('X');
				break;
			default:
				printf("ERROR(1)!");
			}
		}
		putchar('\n');
	}
}
