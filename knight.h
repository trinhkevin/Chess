// knight.h
//
// Contains the Knight class

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

	public:
		Knight(coord, bool);
		virtual deque<coord*> getPossMoves(deque<Piece*>);
	private:
};

Knight::Knight(coord nPosition, bool nColor) : Piece(knight, nPosition, nColor) {
}

deque<coord*> Knight::getPossMoves(deque<Piece*> pieces) {

	// Initialize Variables
        deque<coord*> moves;
        coord* ncoord;
        int x = (*getPosition())[0];
        int y = (*getPosition())[1];

        ncoord = new coord[1];
        (*ncoord)[0] = x-1; (*ncoord)[1] = y-2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        ncoord = new coord[1];
        (*ncoord)[0] = x-2; (*ncoord)[1] = y-1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        ncoord = new coord[1];
        (*ncoord)[0] = x-2; (*ncoord)[1] = y+1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        ncoord = new coord[1];
        (*ncoord)[0] = x-1; (*ncoord)[1] = y+2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        ncoord = new coord[1];
        (*ncoord)[0] = x+1; (*ncoord)[1] = y+2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        ncoord = new coord[1];
        (*ncoord)[0] = x+2; (*ncoord)[1] = y+1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        ncoord = new coord[1];
        (*ncoord)[0] = x+2; (*ncoord)[1] = y-1;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        ncoord = new coord[1];
        (*ncoord)[0] = x+1; (*ncoord)[1] = y-2;
        if( !checkSpace( ncoord, getColor(), pieces ) )
          moves.push_back(ncoord);
        else
          delete[] ncoord;

        return moves;

}

#endif
