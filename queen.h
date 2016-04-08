// queen.h
//
// Contains the Queen class

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

	public:
		Queen(coord, bool);
	        virtual deque<coord> getPossMoves( Piece* [8][8], Piece* );
	private:
};

Queen::Queen(coord nPosition, bool nColor) : Piece(queen, nPosition, nColor) {
}

deque<coord> Queen::getPossMoves( Piece* spaces[8][8], Piece* enPass) {

	// This deque will contain all locations,
	// on or off the board, that are less than
	// a distance of 8 in all 8 directions from
	// the Queen

	deque<coord> moves;

	scan( -1,  0, 7, moves, spaces );
	scan( -1,  1, 7, moves, spaces );
	scan(  0,  1, 7, moves, spaces );
	scan(  1,  1, 7, moves, spaces );
	scan(  1,  0, 7, moves, spaces );
	scan(  1, -1, 7, moves, spaces );
	scan(  0, -1, 7, moves, spaces );
	scan( -1, -1, 7, moves, spaces );

	return moves;
}

#endif
