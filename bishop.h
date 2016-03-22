// bishop.h
//
// Contains the Rook class

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

	public:
		Bishop(int, bool);
		//deque<coord> getPossMoves();
	private:
};

Bishop::Bishop(int nPosition, bool nColor) : Piece(bishop, nPosition, nColor) {
}
/*
deque<coord> Bishop::getPossMoves() {

	// This deque will contain all locations, on or off
	// the board, that are less than a distance of 8 in
	// all four diagonal directions from the bishop

	// Initialize Variables
	pos = getPosition();
	int x = pos[0];
	int y = pos[1];
	deque<coord> possMoves;

	// Loop and Find Possible Moves
	for(int i = 1; i < 8; ++i) {
		possMoves.push_back([x+i, y+i]);
		possMoves.push_back([x+i, y-i]);
		possMoves.push_back([x-i, y+i]);
		possMoves.push_back([x-i, y-i]);
	}

	return possMoves;
}
*/
#endif
