#include "Board.h"

Board::Board() {
}

Board::Board(Piece _data[MAX_ROWS][MAX_COLS]) {
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int k = 0; k < MAX_COLS; k++) {
			data[i][k] = _data[i][k];
		}
	}
}

Piece Board::getPiece(int x, int y) {
	return data[x][y];
}

Board Board::getCopy() {
	return Board(data);
}

void Board::makeMove(Move m) {
	data[getFirstFreeRow(m.col)][m.col] = m.piece;
	setResult(m.col);
}

Result Board::getResult() {
	return result;
}

void Board::printBoard() {
	for (int i = 0; i < MAX_COLS; i++) {
		cout << "------------------------------" << endl;
		for (int k = 0; k < MAX_ROWS; k++) {
			cout << "|" << " " << data[k][i] << " ";
		}
		cout << "|" << endl;
	}
	cout << "------------------------------" << endl;
}

int Board::getFirstFreeRow(int col) {
	for (int i = 0; i < MAX_ROWS; i++) {
		if (data[i][col] == EMPTY) {
			return i;
		}
	}
	return MAX_ROWS;
}

void Board::retractMove(Move m) {
	data[getFirstFreeRow(m.col) - 1][m.col] = EMPTY;
	setResult(m.col);
}

void Board::setResult(int col) {
	if (isFourInRow(PLAYER1, col)) {
		result = P1WIN;
	} else if (isFourInRow(PLAYER2, col)) {
		result = P2WIN;
	} else if (isFull()) {
		result = DRAW;
	} else {
		result = NO_RESULT;
	}
}

bool Board::isFull() {
	for (int i = 0; i < MAX_COLS; i++) {
		if (data[MAX_ROWS-1][i] == EMPTY) {
			return false;
		}
	}
	return true;
}

bool Board::isFourInRow(Piece p, int col) {
	for (int i = 0; i < MAX_COLS; i++) {
		for (int k = 0; k < MAX_ROWS; k++) {
			if (data[k][i] == p && piecesInDirection(k, i, -1, 0) + piecesInDirection(i, k, 1, 0) == 3) {
				return true;
			}
			if (data[k][i] == p && piecesInDirection(k, i, 0, -1) + piecesInDirection(i, k, 0, 1) == 3) {
				return true;
			}
			if (data[k][i] == p && piecesInDirection(k, i, 1, -1) + piecesInDirection(i, k, -1, 1) == 3) {
				return true;
			}
			if (data[k][i] == p && piecesInDirection(k, i, 1, 1) + piecesInDirection(i, k, -1, -1) == 3) {
				return true;
			}
		}
	}
	return false;
}

int Board::piecesInDirection(int x, int y, int dx, int dy) {
	int count = 0;
	for (int i = 0; x + dx * i < MAX_ROWS && y + dy * i < MAX_COLS; i++) {
		if (data[x][y] == data[x + dx * i][y + dy * i]) {
			count++;
		} else {
			return count;
		}
	}
	return count;
}