// queen.h
//
// Contains the Queen class

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

	public:
		Queen(coord, bool);
		deque<coord> getPossMoves();
	private:
}

Queen::Queen(coord position, bool color) : Piece("Queen", position, color) {
}

deque<coord> Queen::getPossMoves() {

	// This deque will contain all locations,
	// on or off the board, that are less than
	// a distance of 8 in all 8 directions from
	// the Queen

	// Initialize Variables
	pos = getPosition();
	int x = pos[0];
	int y = pos[1];
	deque<coord> possMoves;

	// Compute Possible Moves
	for(int i = 1; i < 8; ++i) {
    		possMoves.push_back([x+i, y+i]);
    		possMoves.push_back([x+i, y-i]);
    		possMoves.push_back([x-i, y+i]);
    		possMoves.push_back([x-i, y-i]);
    		possMoves.push_back([x, y+i]);
    		possMoves.push_back([x, y-i]);
    		possMoves.push_back([x+i, y]);
    		possMoves.push_back([x-i, y]);
	}

	return possMoves;
}

#endif
