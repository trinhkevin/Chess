// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
	Pawn(coord, bool);
	virtual deque<coord> getPossMoves( deque<Piece*> );
    private:
};

Pawn::Pawn(coord nPosition, bool nColor) : Piece(pawn, nPosition, nColor) {
}

deque<coord> Pawn::getPossMoves( deque<Piece*> pieces ){

	// Initialize Variables
	deque<coord> moves;
	coord ncoord;
	int x = getPosition().x;
	int y = getPosition().y;

	// Compute Moves
	ncoord.x = x; ncoord.y = y+1-getColor()*2;
	  
        if( !checkSpace( ncoord, getColor(), pieces ) && 
            !checkSpace( ncoord, !getColor(), pieces ))
          moves.push_back(ncoord);
	
	if( moves.size()==1 && !getHasMoved()) {
	  ncoord.x = x; ncoord.y = y+2-getColor()*4;

        if( !checkSpace( ncoord, getColor(), pieces ) &&
            !checkSpace( ncoord, !getColor(), pieces ))
          moves.push_back(ncoord); 
	}

	ncoord.x = x-1; ncoord.y = y+1-getColor()*2;

	if(checkSpace( ncoord, !getColor(), pieces ))
	  moves.push_back(ncoord);

	ncoord.x = x+1; ncoord.y = y+1-getColor()*2;

	if(checkSpace( ncoord, !getColor(), pieces ))
	  moves.push_back(ncoord);

	return moves;
}

#endif
