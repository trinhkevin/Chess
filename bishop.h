// bishop.h
//
// Contains the Rook class

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

	public:
		Bishop(coord, bool);
		virtual deque<coord> getPossMoves( Piece*[8][8], Piece* );
	private:
};

Bishop::Bishop(coord nPosition, bool nColor) : Piece(bishop, nPosition, nColor) {
}

deque<coord> Bishop::getPossMoves( Piece* spaces[8][8], Piece* enPass) {

	// This deque will contain all locations, on or off
	// the board, that are less than a distance of 8 in
	// all four diagonal directions from the bishop

	// Initialize Variables
	deque<coord> moves;

        scan( -1,  1, 7, moves, spaces );
        scan(  1,  1, 7, moves, spaces );
        scan(  1, -1, 7, moves, spaces );
        scan( -1, -1, 7, moves, spaces );

        return moves;
}

#endif
