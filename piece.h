// piece.h
//
// Contains the Piece class

#ifndef PIECE_H
#define PIECE_H

#include "LTexture.h"
#include <deque>

using std::deque;

const int CLIPNUM = 13;
enum pieceType{ king, queen, bishop, knight, rook, pawn };
typedef int coord[2];

class Piece {

	public:
		Piece(pieceType nType, coord nPosition, bool nColor);
		coord* getPosition()  { return &position; }
		void setPosition(coord nPosition);
		pieceType getType()   { return type; }
		void select()         { selected = true; }
                void deselect()       { selected = false; }
		void display(SDL_Renderer*, LTexture&, SDL_Rect[CLIPNUM], int);
		//virtual deque<coord> getPossMoves() = 0;
	private:
		coord position;
		pieceType type;
		bool color;
		bool selected = false;
};

Piece::Piece(pieceType nType, coord nPosition, bool nColor) {
	type = nType;
	setPosition(nPosition);
	color = nColor;
}

void Piece::setPosition(coord nPosition) {
	position[0] = nPosition[0];
	position[1] = nPosition[1];
}

void Piece::display(SDL_Renderer* gRenderer, LTexture &texture, SDL_Rect clips[CLIPNUM], int SIDE) {
  //glow if selected
  if(selected)	
    texture.render(gRenderer, SIDE/8*(position[0]), SIDE/8*7-SIDE/8*(position[1]), &clips[12]);

  //render piece
  texture.render(gRenderer, SIDE/8*(position[0]), SIDE/8*7-SIDE/8*(position[1]), &clips[type + color*6]);
}

#endif
