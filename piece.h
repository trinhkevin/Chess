// piece.h
//
// Contains the Piece class

#ifndef PIECE_H
#define PIECE_H

#include "LTexture.h"
#include <deque>
using std::deque;

const int CLIPNUM = 17;
enum pieceType{ king, queen, bishop, knight, rook, pawn };

struct coord
{
  int x;
  int y;

  inline bool operator==(coord a) {
    if (a.x==x && a.y== y)
      return true;
    else
      return false;
  }

};


class Piece {

	public:
		Piece(pieceType, coord, bool nColor );
		coord getPosition()	{ return position; }
		void move(coord, Piece* [8][8]);
		void revert(Piece*[8][8]);
		pieceType getType()const{ return type; }
		bool getHasMoved()const { return hasMoved; }
		bool getColor()const	{ return color; }
		virtual deque<coord> getPossMoves( Piece*[8][8],Piece*) = 0;
		void scan(int,int,int,deque<coord>&, Piece*[8][8] );
		void display(SDL_Renderer*, LTexture&, SDL_Rect[CLIPNUM], int);
	private:
		coord position;
		coord lastPosition;
		pieceType type;
		bool color;
		bool hasMoved = false;
		bool firstMove = true;
};

Piece::Piece(pieceType nType, coord nPosition, bool nColor)
      : position(nPosition), type(nType), color(nColor) {}

void Piece::move(coord nPosition, Piece* spaces[8][8]) {

	lastPosition = position;
	spaces[position.x][position.y] = NULL;
	position = nPosition;
	spaces[position.x][position.y] = this;

	if(hasMoved)
		firstMove = false;

	hasMoved = true;
}

void Piece::revert(Piece* spaces[8][8]) {

	if(type==king) {
          if(lastPosition.x-position.x == 2)
	    spaces[position.x+1][position.y]->revert(spaces);
          if(lastPosition.x-position.x == -2)
	    spaces[position.x-1][position.y]->revert(spaces);
	}
          
	spaces[position.x][position.y] = NULL;
	position = lastPosition;
	spaces[position.x][position.y] = this;

	if(firstMove)
		hasMoved = false;
}

void Piece::scan(int x,int y,int range,deque<coord>& moves,Piece* spaces[8][8])
{

  for( int i = 1; i <= range; i++ ) {
    coord space;
    space.x = position.x + i*x;
    space.y = position.y + i*y;
    //edge of board
    if(space.x < 0 || space.x > 7 || space.y < 0 || space.y > 7 )
      return;

    if(spaces[space.x][space.y] == NULL )
      moves.push_back(space);
    else if (spaces[space.x][space.y]->getColor() == color)
      return;
    else {
      moves.push_back(space);
      return;
    }

  }
}

void Piece::display(SDL_Renderer* gRenderer, LTexture &texture, 
                    SDL_Rect clips[CLIPNUM], int SIDE) {

  //render piece
  texture.render(gRenderer, SIDE/8*position.x, 
                 SIDE/8*7-SIDE/8*position.y, &clips[type + color*6]);
}

#endif
