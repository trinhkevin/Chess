// king.h
//
// Contains the King class

#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {

	public:
		King(coord, bool);
		//deque<int> getPossMoves();
	private:
};

King::King(coord nPosition, bool nColor) : Piece(king, nPosition, nColor) {
}
/*
deque<coord> King::getPosition() {

	// Initialize Variables
	coord position = getPosition();
	coord nCoord;
	i = position[0];
	j = position[1];
	deque<coord> possMoves;

	// Up
	nCoord = [i, j+1];
	possMove.push_back(nCoord);

	// Down
	nCoord = [i, j-1];
	possMove.push_back(nCoord);

	// Left
	nCoord = [i-1, j];
	possMove.push_back(nCoord);

	// Right
	nCoord = [i+1, j];
	possMove.push_back(nCoord);

	// Top-Left
	nCoord = [i-1, j+1];
	possMove.push_back(nCoord);

	// Top-Right
	nCoord = [i+1, j+1];
	possMove.push_back(nCoord);

	// Bottom-Left
	nCoord = [i-1, j-1];
	possMove.push_back(nCoord);

	// Bottom-Right
	nCoord = [i+1, j-1];
	possMove.push_back(nCoord);

	return possMoves;
}*/

#endif
