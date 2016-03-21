// knight.h
//
// Contains the Knight class

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

	public:
		Knight(coord);
		deque<coord> getPossMoves();
	private:
}

Knight(coord nPosition) : Piece("Knight", nPosition) {
}

deque<coord> getPossMoves() {

	// Initialize Variables
	coord position = getPosition();
	coord nCoord;
	i = position[0];
	j = position[1];
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
