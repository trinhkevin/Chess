// bishop.h
//
// Contains the Rook class

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

	public:
		Bishop(coord, bool);
		virtual deque<coord> getPossMoves( Piece*[8][8] );
	private:
};

Bishop::Bishop(coord nPosition, bool nColor) : Piece(bishop, nPosition, nColor) {
}

deque<coord> Bishop::getPossMoves( Piece* spaces[8][8]) {

	// This deque will contain all locations, on or off
	// the board, that are less than a distance of 8 in
	// all four diagonal directions from the bishop

	// Initialize Variables
	deque<coord> moves;

        range( -1, 1, moves, spaces );
        range( 1, 1, moves, spaces );
        range( 1, -1, moves, spaces );
        range( -1, -1, moves, spaces );

        return moves;
}

#endif
