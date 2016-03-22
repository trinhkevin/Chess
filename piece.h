// piece.h
//
// Contains the Piece class

#ifndef PIECE_H
#define PIECE_H

#include "LTexture.h"
#include <deque>

using std::deque;

enum pieceType{ king, queen, bishop, knight, rook, pawn };
typedef int coord[2];

class Piece {

	public:
		Piece(pieceType nType, coord nPosition, bool nColor);
		coord* getPosition();
		void setPosition(coord nPosition);
		pieceType getType();
		void display(SDL_Renderer*, LTexture&, SDL_Rect[12], int);
		//virtual deque<coord> getPossMoves() = 0;
	private:
		coord position;
		pieceType type;
		bool color;
};

Piece::Piece(pieceType nType, coord nPosition, bool nColor) {
	type = nType;
	setPosition(nPosition);
	color = nColor;
}

coord* Piece::getPosition() {
	return &position;
}

void Piece::setPosition(coord nPosition) {
	position[0] = nPosition[0];
	position[1] = nPosition[1];
}

pieceType Piece::getType() {
	return type;
}

void Piece::display(SDL_Renderer* gRenderer, LTexture &texture, SDL_Rect clips[12], int SIDE) {
	texture.render(gRenderer, SIDE/8*(position[0]), SIDE/8*7-SIDE/8*(position[1]), &clips[type + color*6]);
}

#endif
