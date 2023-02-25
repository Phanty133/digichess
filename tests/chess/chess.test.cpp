#include "gtest/gtest.h"

extern "C" {
	#include "../include/chess/chess.h"
}

TEST(Chess, move_piece){
	int flag;
	ChessBoard chess_board;
	ChessBoard* board = &chess_board;
	arrange_board(board);
	
	flag = move_piece(board, 1, 4, 3, 4); //1
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 6, 4, 4, 4); //2
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 1, 3, 3, 3); //3
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 4, 3, 3); //4
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 0, 3, 3, 3); //5
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 7, 1, 5, 2); //6
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 3, 3, 4, 3); //7
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 7, 6, 5, 5); //8
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 3, 4, 5); //9
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 6, 6, 5, 6 ); //10
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 5, 4, 6); //11
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 7, 5, 4, 2); //12
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 6, 4, 2); //13
	EXPECT_EQ(flag, 1);

	// A new Game
	arrange_board(board);

	flag = move_piece(board, 1, 4, 3, 4); //14
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 6, 0, 4, 0); //15
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 3, 4, 4, 4); //16
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 0, 3, 0); //17
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 5, 5, 5); //18
	EXPECT_EQ(flag, -2);

	flag = move_piece(board, 4, 4, 5, 4); //19
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 6, 1, 5, 1); //20
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 1, 1, 3, 1); //21
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 3, 0, 2, 1); 
	EXPECT_EQ(flag, 4);

	flag = move_piece(board, 5, 4, 6, 5); 
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 2, 1, 1, 2); 
	EXPECT_EQ(flag, -1);

	flag = move_piece(board, 7, 4, 6, 5); 
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 0, 3, 1, 4); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 7, 0, 4, 0); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 1, 0, 2, 1); 
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 4, 0, 4, 4); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 1, 4, 2, 5); // Pinned 
	EXPECT_EQ(flag, -1);

	flag = move_piece(board, 1, 4, 4, 4); 
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 7, 3, 7, 4); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 4, 4, 5); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 6, 5, 5, 6); 
	EXPECT_EQ(flag, -1);

	flag = move_piece(board, 7, 1, 4, 0); 
	EXPECT_EQ(flag, -1);

	flag = move_piece(board, 7, 1, 5, 0); 
	EXPECT_EQ(flag, -1);

	flag = move_piece(board, 7, 6, 5, 5); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 5, 4, 6); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 5, 5, 3, 4); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 2, 1, 3, 1); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 3, 4, 1, 3); 
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 0, 4, 1, 3); 
	EXPECT_EQ(flag, 1);

	flag = move_piece(board, 7, 7, 7, 6); 
	EXPECT_EQ(flag, 0);

	flag = move_piece(board, 4, 6, 4, 5); // 44
	EXPECT_EQ(flag, 6);

	// Game 3
	empty_board(board);
	place_at(board, 0, 1, wRook);
	place_at(board, 1, 2, wRook);
	place_at(board, 5, 0, bKing);
	place_at(board, 4, 4, wKing);
	flag = move_piece(board, 1, 2, 1, 0); // 45
	EXPECT_EQ(flag, 6);

	// Game 4
	empty_board(board);
	place_at(board, 0, 1, bRook);
	place_at(board, 1, 2, bRook);
	place_at(board, 5, 0, wKing);
	place_at(board, 4, 4, bKing);
	board->whites_turn = false;
	flag = move_piece(board, 1, 2, 1, 0); // 46
	EXPECT_EQ(flag, 7);

	// Game 5	
	empty_board(board);
	place_at(board, 0, 1, wRook);
	place_at(board, 4, 6, wRook);
	place_at(board, 2, 2, wBishop);
	place_at(board, 5, 0, bKing);
	place_at(board, 7, 7, wKing);
	flag = move_piece(board, 2, 2, 3, 3); // 47
	EXPECT_EQ(flag, 5);


	// Game 6	
	empty_board(board);
	place_at(board, 0, 1, bRook);
	place_at(board, 4, 6, bRook);
	place_at(board, 2, 2, bBishop);
	place_at(board, 5, 0, wKing);
	place_at(board, 7, 7, bKing);
	board->whites_turn = false;
	flag = move_piece(board, 2, 2, 3, 3); // 48
	EXPECT_EQ(flag, 5);


}