// piece.h
//
// Contains the Piece class

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <deque>

typedef coord int[2];

class Piece {

	public:
		Piece(string nName, coord nPosition, bool nColor);
		virtual coord getPosition();
		virtual void setPosition(coord nPosition);
		virtual string getName();
		virtual deque<coord> getPossMoves() = 0;
	private:
		coord position;
		string name;
		bool color;
};

Piece::Piece(string nName, coord nPosition, bool nColor) {
	name = nName;
	setPosition(coord);
	color = nColor;
}

coord Piece::getPosition() {
	return position;
}

void Piece::setPosition(coord nPosition) {
	position = nPosition;
}

string Piece::getName() {
	return name;
}

/* deque<coord> Piece::getPossMoves() {
	return possMoves;
} */

#endif
