// piece.h
//
// Prototype for Piece class

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <deque>

typedef move int[2];

class Piece {

	public:
		int[2] getPosition() = 0;
		void setPosition(int, int) = 0;
		string getName() = 0;
		deque<int{2]> getPossMoves() = 0;
	private:
		int position[2];
		string name;
		deque<int> possMoves;
};

int[2] Piece::getPosition() {
	return position;
}

void Piece::setPosition(int x, int y) {
	position[2] = [x, y];
}

string Piece::getName() {
	return name;
}

deque Piece::getPossMoves() {
	return possMoves;
}

#endif
