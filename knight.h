// knight.h
//
// Contains the Knight class

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

	public:
		Knight(coord, bool);
	        virtual deque<coord> getPossMoves( Piece*[8][8], Piece* );
	private:
};

Knight::Knight(coord nPosition, bool nColor) : Piece(knight, nPosition, nColor) {
}

deque<coord> Knight::getPossMoves( Piece* spaces[8][8], Piece* enPass) {

	// Initialize Variables
        deque<coord> moves;

    // Return Moves
	scan( -2,  1, 1, moves, spaces );
	scan( -1,  2, 1, moves, spaces );
	scan(  1,  2, 1, moves, spaces );
	scan(  2,  1, 1, moves, spaces );
	scan(  2, -1, 1, moves, spaces );
	scan(  1, -2, 1, moves, spaces );
	scan( -1, -2, 1, moves, spaces );
	scan( -2, -1, 1, moves, spaces );

        return moves;
}

#endif
