#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
using namespace std;

struct Move {
	int col;
	Piece piece;
};

enum Piece {
	EMPTY, PLAYER1, PLAYER2
};

enum Result {
	DRAW, P1WIN, P2WIN, NO_RESULT
};

const int MAX_ROWS = 6;
const int MAX_COLS = 7;

class Board {
public:
	Board();
	Board(Piece[MAX_ROWS][MAX_COLS]);
	Board getCopy();
	Piece getPiece(int, int);
	void makeMove(Move);
	Result getResult();
	void printBoard();
	int getFirstFreeRow(int);
	void retractMove(Move);
private:
	Piece data[MAX_ROWS][MAX_COLS];
	Result result;
	void setResult(int);
	bool isFourInRow(Piece, int);
	bool isFull();
	int piecesInDirection(int, int, int, int);
};

#endif