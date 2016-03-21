// queen.h
//
// Contains the Queen class

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

	public:
		Queen(string nName, coord nPosition);
		deque<coord> getPossMoves();
	private:
}

Queenp(string nName, coord nPosition):Piece(nName, nPosition) {
}

deque<coord> getPossMoves() {
  //This deque will contain all locations, on or off the board, that are less than a distance of 8 in all 8 directions from the Queen
  pos = getPosition();
  int x = pos[0];
  int y = pos[1];
  deque<coord> possMoves;

  for(int i=1; counter < 8; ++ counter) {
    possMoves.push_back([x+i, y+i]);
    possMoves.push_back([x+i, y-i]);
    possMoves.push_back([x-i, y+i]);
    possMoves.push_back([x-i, y-i]);
    possMoves.push_back([x, y+i]);
    possMoves.push_back([x, y-i]);
    possMoves.push_back([x+i, y]);
    possMoves.push_back([x-i, y]);
}

#endif
