// rook.h
//
// Contains the Rook class

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {

	public:
		Rook(coord, bool);
	        virtual deque<coord> getPossMoves( Piece*[8][8] );
	private:
		bool hasMoved = false;
};

Rook::Rook(coord nPosition, bool nColor) : Piece(rook, nPosition, nColor) {
}

deque<coord> Rook::getPossMoves( Piece* spaces[8][8] ) {

	// The positions on this deque will be
	// all positions on the board in the same
	// row or column as the piece, except for
	// the piece's current position

	// Initialize Variables

	deque<coord> moves;

        range( -1, 0, moves, spaces );
        range( 0, 1, moves, spaces );
        range( 1, 0, moves, spaces );
        range( 0, -1, moves, spaces );

        return moves;

}

#endif
