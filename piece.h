// piece.h
//
// Contains the Piece class

#ifndef PIECE_H
#define PIECE_H

#include "LTexture.h"
#include <deque>

using std::deque;

const int CLIPNUM = 14;
enum pieceType{ king, queen, bishop, knight, rook, pawn };
typedef int coord[2];

class Piece {

	public:
		Piece(pieceType nType, coord nPosition, bool nColor);
		~Piece() { deselect(); }
		coord* getPosition()	{ return &position; }
		void move(coord nPosition);
		pieceType getType()	{ return type; }
		bool getHasMoved()	{ return hasMoved; }
		bool getColor()		{ return color; }
		void select()		{ selected = true; }
		bool getSelected() 	{ return selected; }
                void deselect()		{ selected = false; }
		virtual deque<coord*> getPossMoves(deque<Piece*>) = 0;
		bool checkSpace( coord*, bool, deque<Piece*> );
		void range( int x, int y, deque<coord*>&, deque<Piece*> );
		void display(SDL_Renderer*, LTexture&, SDL_Rect[CLIPNUM], int);
	private:
		coord position;
		pieceType type;
		bool color;
		bool selected = false;
		bool hasMoved = false;
};

Piece::Piece(pieceType nType, coord nPosition, bool nColor) {
	
	position[0] = nPosition[0];
	position[1] = nPosition[1];

	type = nType;
	color = nColor;
}

bool Piece::checkSpace( coord* space, bool col, deque<Piece*> pieces) {

  bool blocked = false;

  for(int i = 0; i < pieces.size(); i++)
    if( (*pieces[i]->getPosition())[0] == (*space)[0] &&
        (*pieces[i]->getPosition())[1] == (*space)[1] &&
        pieces[i]->getColor() == col)
          blocked = true;

  return blocked;
}

void Piece::move(coord nPosition) {
	position[0] = nPosition[0];
	position[1] = nPosition[1];
	hasMoved = true;
	deselect();
}

void Piece::range( int x, int y, deque<coord*>& moves, deque<Piece*> pieces) {

  for( int i = 1; i <= 8; i++ ) {
    coord* space = new coord[1];
    (*space)[0] = (*getPosition())[0] + i*x;
    (*space)[1] = (*getPosition())[1] + i*y;
    if(checkSpace( space, getColor(), pieces)) {
      delete space;
      return;
    }
    moves.push_back(space);

    if(checkSpace( space, !getColor(), pieces))
      return;
  }
}

void Piece::display(SDL_Renderer* gRenderer, LTexture &texture, 
                    SDL_Rect clips[CLIPNUM], int SIDE) {

  //glow and show moves if selected
  if(selected) 
    texture.render(gRenderer, SIDE/8*(position[0]), 
                   SIDE/8*7-SIDE/8*(position[1]), &clips[12]);

  //render piece
  texture.render(gRenderer, SIDE/8*(position[0]), 
                 SIDE/8*7-SIDE/8*(position[1]), &clips[type + color*6]);
}

#endif
