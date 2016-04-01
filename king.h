// king.h
//
// Contains the King class

#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {

	public:
		King(coord, bool);
		virtual deque<coord*> getPossMoves(deque<Piece*>);
	private:
};

King::King(coord nPosition, bool nColor) : Piece(king, nPosition, nColor) {
}

deque<coord*> King::getPossMoves( deque<Piece*> pieces) {

	// Initialize Variables
        deque<coord*> moves;
        coord* ncoord;
        int x = (*getPosition())[0];
        int y = (*getPosition())[1];


	for(int i = 0; i < 9; i++)
          if( i != 4 ) {

	    ncoord = new coord[1];
            (*ncoord)[0] = x-1+i%3; (*ncoord)[1] = y-1+i/3;
            if( !checkSpace( ncoord, getColor(), pieces ) )
              moves.push_back(ncoord);
            else
              delete[] ncoord;
	  }

	return moves;
}

#endif
