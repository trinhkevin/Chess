// piece.h
//
// Contains the Piece class

#ifndef PIECE_H
#define PIECE_H

#include "LTexture.h"
#include <deque>

enum pieceType{ king, queen, bishop, knight, rook, pawn };

class Piece {

	public:
		Piece(pieceType nType, int nPosition, bool nColor);
		int getPosition();
		void setPosition(int nPosition);
		pieceType getType();
		void display(SDL_Renderer*, LTexture&, SDL_Rect[12], int);
		//virtual deque<coord> getPossMoves() = 0;
	private:
		//tiles numbered 0 through 63 from top left for position
		int position;
		pieceType type;
		bool color;
};

Piece::Piece(pieceType nType, int nPosition, bool nColor) {
	type = nType;
	setPosition(nPosition);
	color = nColor;
}

int Piece::getPosition() {
	return position;
}

void Piece::setPosition(int nPosition) {
	position = nPosition;
}

pieceType Piece::getType() {
	return type;
}

void Piece::display(SDL_Renderer* gRenderer, LTexture &texture, SDL_Rect clips[12], int SIDE) {
	texture.render(gRenderer, SIDE/8*(position%8), SIDE/8*(position/8), &clips[type + color*6]);
}

/* deque<coord> Piece::getPossMoves() {
	return possMoves;
} */

#endif
