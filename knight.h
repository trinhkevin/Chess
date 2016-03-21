// knight.h
//
// Contains the Knight class

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

	public:
		Knight(coord, bool);
		deque<coord> getPossMoves();
	private:
}

Knight::Knight(coord position, bool color) : Piece("Knight", position, color) {
}

deque<coord> Knight::getPossMoves() {

	// Initialize Variables
	coord position = getPosition();
	coord nCoord;
	int i = position[0];
	int j = position[1];
	deque<coord> possMoves;

	// Up Right
	nCoord = [i+1, j+2];
	possMove.push_back(nCoord);

	// Up Left
	nCoord = [i-1, j+2];
	possMove.push_back(nCoord);

	// Down Right
	nCoord = [i+1, j-2];
	possMove.push_back(nCoord);

	// Down Left
	nCoord = [i-1, j-2];
	possMove.push_back(nCoord);

	return possMoves;
}

#endif
