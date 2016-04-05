// knight.h
//
// Contains the Knight class

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

	public:
		Knight(coord, bool);
		virtual deque<coord> getPossMoves(deque<Piece*>);
	private:
};

Knight::Knight(coord nPosition, bool nColor) : Piece(knight, nPosition, nColor) {
}

deque<coord> Knight::getPossMoves(deque<Piece*> pieces) {

	// Initialize Variables
        deque<coord> moves;
        coord ncoord;
	int x = getPosition().x;
	int y = getPosition().y;

        ncoord.x = x-1; ncoord.y = y-2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        ncoord.x = x-2; ncoord.y = y-1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        ncoord.x = x-2; ncoord.y = y+1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        ncoord.x = x-1; ncoord.y = y+2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        ncoord.x = x+1; ncoord.y = y+2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        ncoord.x = x+2; ncoord.y = y+1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        ncoord.x = x+2; ncoord.y = y-1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        ncoord.x = x+1; ncoord.y = y-2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);

        return moves;

}

#endif
