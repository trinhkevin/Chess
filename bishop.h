// bishop.h
//
// Contains the Rook class

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

	public:
		Bishop(coord, bool);
		deque<coord*> getPossMoves( deque<Piece*> );
	private:
};

Bishop::Bishop(coord nPosition, bool nColor) : Piece(bishop, nPosition, nColor) {
}

deque<coord*> Bishop::getPossMoves( deque<Piece*> pieces ) {

	// This deque will contain all locations, on or off
	// the board, that are less than a distance of 8 in
	// all four diagonal directions from the bishop

	// Initialize Variables
	deque<coord*> moves;

        range( -1, 1, moves, pieces );
        range( 1, 1, moves, pieces );
        range( 1, -1, moves, pieces );
        range( -1, -1, moves, pieces );

        return moves;
}

#endif
