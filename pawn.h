// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
        Pawn(string name, position);
		virtual deque<coord> getPossMoves() = 0;
    private:
        bool hasMoved() = false;
}

Pawn(coord position):Piece("Pawn", position){
}

deque<coord> getPossMoves(){
    deque<coord> moves;
    coord pos = getPosition();
    coord ncoord;

    x = pos[0];
    y = pos[1];

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

#endif
