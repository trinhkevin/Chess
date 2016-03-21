// bishop.h
//
// Contains the Rook class

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

	public:
		Bishop(string nName, coord nPosition);
		deque<coord> getPossMoves();
	private:
}

Bishop(string nName, coord nPosition):Piece(nName, nPosition) {
}

deque<coord> getPossMoves() {
  //This deque will contain all locations, on or off the board, that are less than a distance of 8 in all four diagonal directions from the bishop
  pos = getPosition();
  int x = pos[0];
  int y = pos[1];
  deque<coord> possMoves;

  for(int i=1; counter < 8; ++ counter) {
    possMoves.push_back([x+i, y+i]);
    possMoves.push_back([x+i, y-i]);
    possMoves.push_back([x-i, y+i]);
    possMoves.push_back([x-i, y-i]);
}

#endif
