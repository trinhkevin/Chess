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

struct coord
{
  int x;
  int y;
};

class Piece {

	public:
		Piece(pieceType nType, coord nPosition, bool nColor);
		~Piece() { deselect(); }
		coord getPosition()	{ return position; }
		void move(coord nPosition);
		pieceType getType()	{ return type; }
		bool getHasMoved()	{ return hasMoved; }
		bool getColor()		{ return color; }
		void select()		{ selected = true; }
		bool getSelected() 	{ return selected; }
                void deselect()		{ selected = false; }
		virtual deque<coord> getPossMoves(deque<Piece*>) = 0;
		bool checkSpace( coord, bool, deque<Piece*> );
		void range( int x, int y, deque<coord>&, deque<Piece*> );
		void display(SDL_Renderer*, LTexture&, SDL_Rect[CLIPNUM], int);
		bool isLocated( int, int );
	private:
		coord position;
		pieceType type;
		bool color;
		bool selected = false;
		bool hasMoved = false;
};

Piece::Piece(pieceType nType, coord nPosition, bool nColor) {
	
	position.x = nPosition.x;
	position.y = nPosition.y;

	type = nType;
	color = nColor;
}

bool Piece::checkSpace( coord space, bool col, deque<Piece*> pieces) {

  bool blocked = false;

  for(int i = 0; i < pieces.size(); i++)
    if( pieces[i]->getPosition().x == space.x &&
        pieces[i]->getPosition().y == space.y &&
        pieces[i]->getColor() == col)
          blocked = true;

  return blocked;
}
		
bool Piece::isLocated( int x, int y ) {

  if( position.x == x && position.y == y )
    return true;

  return false;

}

void Piece::move(coord nPosition) {
	position.x = nPosition.x;
	position.y = nPosition.y;
	hasMoved = true;
	deselect();
}

void Piece::range( int x, int y, deque<coord>& moves, deque<Piece*> pieces) {

  for( int i = 1; i <= 8; i++ ) {
    coord space;
    space.x = getPosition().x + i*x;
    space.y = getPosition().y + i*y;
    if(checkSpace( space, getColor(), pieces)) {
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
    texture.render(gRenderer, SIDE/8*position.x, 
                   SIDE/8*7-SIDE/8*position.y, &clips[12]);

  //render piece
  texture.render(gRenderer, SIDE/8*position.x, 
                 SIDE/8*7-SIDE/8*position.y, &clips[type + color*6]);
}

#endif
