// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
        Pawn(int, bool);
	//virtual deque<coord> getPossMoves() = 0;
    private:
};

Pawn::Pawn(int nPosition, bool nColor) : Piece(pawn, nPosition, nColor) {
}

/*deque<coord> Pawn::getPossMoves(){

	// Initialize Variables
	deque<coord> moves;
	coord pos = getPosition();
	coord ncoord;
	int x = pos[0];
	int y = pos[1];

	// Compute Moves
	ncoord = [x, y+1];
	moves.pushback(ncoord);

	ncoord = [x, y+2];
	moves.pushback(ncoord);

	ncoord = [x+1, y+1];
	moves.pushback(ncoord);

	ncoord = [x-1, y+1];
	moves.pushback(ncoord);

	return moves
}
*/
#endif
