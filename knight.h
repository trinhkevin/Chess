// knight.h
//
// Contains the Knight class

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

	public:
		Knight(string nName, coord nPosition);
		coord getPosition();
		void setPosition(coord nPosition);
		string getName();
		deque<coord> getPossMoves();
	private:
}

Knight(string nName, coord nPosition):Piece(nName, nPosition) {
}

coord getPosition() {
	return position;
}

void setPosition(coord nPosition) {
	position = nPosition;
}

string getName() {
	return name;
}

deque<coord> getPossMoves() {
	
}

#endif
