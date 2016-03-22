// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
	Pawn(coord, bool);
	//virtual deque<coord> getPossMoves();
    private:
};

Pawn::Pawn(coord nPosition, bool nColor) : Piece(pawn, nPosition, nColor) {
}
/*
deque<coord> Pawn::getPossMoves(){

	// Initialize Variables
	deque<coord> moves;
	coord* pos = getPosition();
	coord ncoord;
	int x = (*pos)[0];
	int y = (*pos)[1];

	// Compute Moves
	ncoord[0] = x; ncoord[0] = y+1;
	//moves.push_back(ncoord);

	ncoord[0] = y+2;
	//moves.push_back(ncoord);

	ncoord[0] =x+1; ncoord[1] = y+1;
	//moves.push_back(ncoord);

	ncoord[0] = x-1;
	//moves.push_back(ncoord);

	return moves;
}
*/
#endif
