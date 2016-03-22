// board.h
//
// Contains the Board class

#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include <vector>

using std::vector;

#define WHITE 0
#define BLACK 1

class Board {

	public:
		// Constructor
		Board(int side);
		~Board();
		// Member Functions
		void play();
		void display(SDL_Renderer*, LTexture&, SDL_Rect[ 12 ]);
	private:
		// Private Data Members
		const int SIDE;
		vector<Piece*> pieces; // Chess Board

		// Private Helper Functions
};

Board::Board(int nSide) : SIDE(nSide){
  pieces.push_back(new Rook(0,1));
  pieces.push_back(new Knight(1,1));
  pieces.push_back(new Bishop(2,1));
  pieces.push_back(new King(3,1));
  pieces.push_back(new Queen(4,1));
  pieces.push_back(new Bishop(5,1));
  pieces.push_back(new Knight(6,1));
  pieces.push_back(new Rook(7,1));

  pieces.push_back(new Rook(56,0));
  pieces.push_back(new Knight(57,0));
  pieces.push_back(new Bishop(58,0));
  pieces.push_back(new King(59,0));
  pieces.push_back(new Queen(60,0));
  pieces.push_back(new Bishop(61,0));
  pieces.push_back(new Knight(62,0));
  pieces.push_back(new Rook(63,0));
  

  for(int i = 0; i < 8; i++)
  {
    pieces.push_back(new Pawn(8+i,1));
    pieces.push_back(new Pawn(48+i,0));
  }
}

Board::~Board() {

  for(int i = 0; i < pieces.size(); i++)
    delete pieces[i];
}

void Board::display(SDL_Renderer* gRenderer, LTexture &texture, SDL_Rect clips[12]) {

  //Draw board
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
    {
      SDL_Rect fillRect = { SIDE/8*j, SIDE/8*i, SIDE/8*(j+1), SIDE/8*(i+1) };

      //Alternate gray and white
      if( (i+j)%2 )
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
      else
        SDL_SetRenderDrawColor( gRenderer, 0x80, 0x80, 0x80, 0xFF );

      SDL_RenderFillRect( gRenderer, &fillRect );
    }

  for(int i = 0; i < pieces.size(); i++)
    pieces[i]->display( gRenderer, texture, clips, SIDE );

}

void Board::play() {

}

#endif
