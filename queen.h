// queen.h
//
// Contains the Queen class

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

	public:
		Queen(coord, bool);
		deque<coord*> getPossMoves( deque<Piece*> );
	private:
};

Queen::Queen(coord nPosition, bool nColor) : Piece(queen, nPosition, nColor) {
}

deque<coord*> Queen::getPossMoves( deque<Piece*> pieces ) {

	// This deque will contain all locations,
	// on or off the board, that are less than
	// a distance of 8 in all 8 directions from
	// the Queen

	deque<coord*> moves;

	range( -1, 0, moves, pieces );
	range( -1, 1, moves, pieces );
	range( 0, 1, moves, pieces );
	range( 1, 1, moves, pieces );
	range( 1, 0, moves, pieces );
	range( 1, -1, moves, pieces );
	range( 0, -1, moves, pieces );
	range( -1, -1, moves, pieces );

	return moves;
}

#endif
