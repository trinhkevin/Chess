// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
        Pawn(string name, position);
        void setPosition(int, int);
        string getName();
		deque<int{2]> getPossMoves();
    private:

}



#endif
