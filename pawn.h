// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
	Pawn(coord, bool);
    private:
	virtual deque<coord*> findPossMoves();
	bool hasMoved = false;
};

Pawn::Pawn(coord nPosition, bool nColor) : Piece(pawn, nPosition, nColor) {
}

deque<coord*> Pawn::findPossMoves(){

	// Initialize Variables
	deque<coord*> moves;
	coord* ncoord = new coord[1];
	int x = (*getPosition())[0];
	int y = (*getPosition())[1];

	// Compute Moves
	(*ncoord)[0] = x; (*ncoord)[1] = y+1-getColor()*2;
	moves.push_back(ncoord);

	if(!hasMoved) {
	  ncoord = new coord[1];
	  (*ncoord)[0] = x; (*ncoord)[1] = y+2-getColor()*4;
	  moves.push_back(ncoord);
	}

	return moves;
}

#endif
