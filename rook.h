// rook.h
//
// Contains the Rook class

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {

	public:
		Rook(string nName, coord nPosition);
		deque<coord> getPossMoves();
	private:
		bool hasMoved = false;
}

Rook(string nName, coord nPosition):Piece(nName, nPosition) {
}

deque<coord> getPossMoves() {
  //The positions on this deque will be all positions on the board in the same row or column as the piece, except for the piece's current position
  pos = getPosition();
  int x = pos[0];
  int y = pos[1];
  deque<coord> possMoves;

  for(int counter=0; counter < 8; ++ counter) {
    if (counter != x) possMoves.push_back([x, counter]);
    if (counter != y) possMoves.push_back([counter, y]);
}

#endif
