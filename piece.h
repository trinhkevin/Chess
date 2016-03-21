// piece.h
//
// Contains the Piece class

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <deque>

typedef coord int[2];

class Piece {

	public:
		Piece(string nName, coord nPosition);
		coord getPosition() = 0;
		void setPosition(coord) = 0;
		string getName() = 0;
		deque<coord> getPossMoves() = 0;
	private:
		int position[2];
		string name;
};

Piece(string nName, coord nPosition) {
	name = nName;
	setPosition(coord);
}

int[2] Piece::getPosition() {
	return position;
}

void Piece::setPosition(int x, int y) {
	position[2] = [x, y];
}

string Piece::getName() {
	return name;
}

/* deque<coord> Piece::getPossMoves() {
	return possMoves;
} */

#endif
