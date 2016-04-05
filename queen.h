// queen.h
//
// Contains the Queen class

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

	public:
		Queen(coord, bool);
	        virtual deque<coord> getPossMoves( Piece* [8][8] );
	private:
};

Queen::Queen(coord nPosition, bool nColor) : Piece(queen, nPosition, nColor) {
}

deque<coord> Queen::getPossMoves( Piece* spaces[8][8]) {

	// This deque will contain all locations,
	// on or off the board, that are less than
	// a distance of 8 in all 8 directions from
	// the Queen

	deque<coord> moves;

	range( -1, 0, moves, spaces );
	range( -1, 1, moves, spaces );
	range( 0, 1, moves, spaces );
	range( 1, 1, moves, spaces );
	range( 1, 0, moves, spaces );
	range( 1, -1, moves, spaces );
	range( 0, -1, moves, spaces );
	range( -1, -1, moves, spaces );

	return moves;
}

#endif
