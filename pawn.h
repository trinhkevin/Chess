// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
	Pawn(coord, bool);
	virtual deque<coord*> findPossMoves( deque<Piece*> );
    private:
};

Pawn::Pawn(coord nPosition, bool nColor) : Piece(pawn, nPosition, nColor) {
}

deque<coord*> Pawn::findPossMoves( deque<Piece*> pieces ){

	// Initialize Variables
	deque<coord*> moves;
	coord* ncoord = new coord[1];
	int x = (*getPosition())[0];
	int y = (*getPosition())[1];

	// Compute Moves
	(*ncoord)[0] = x; (*ncoord)[1] = y+1-getColor()*2;
	  
        if( !checkSpace( ncoord, getColor(), pieces ) && 
            !checkSpace( ncoord, !getColor(), pieces ))
          moves.push_back(ncoord);
	else
	  delete[] ncoord;
	
	if( moves.size()==1 && !getHasMoved()) {
	  ncoord = new coord[1];
	  (*ncoord)[0] = x; (*ncoord)[1] = y+2-getColor()*4;

        if( !checkSpace( ncoord, getColor(), pieces ) &&
            !checkSpace( ncoord, !getColor(), pieces ))
          moves.push_back(ncoord);
	else
	  delete[] ncoord;
	  
	}

	ncoord = new coord[1];
	(*ncoord)[0] = x-1; (*ncoord)[1] = y+1-getColor()*2;

	if(checkSpace( ncoord, !getColor(), pieces ))
	  moves.push_back(ncoord);
	else
	  delete[] ncoord;

	ncoord = new coord[1];
	(*ncoord)[0] = x+1; (*ncoord)[1] = y+1-getColor()*2;

	if(checkSpace( ncoord, !getColor(), pieces ))
	  moves.push_back(ncoord);
	else
	  delete[] ncoord;

	return moves;
}

#endif
