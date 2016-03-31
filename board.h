// board.h
//
// Contains the Board class

#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "piece.h"
//#include "bishop.h"
//#include "king.h"
//#include "knight.h"
#include "pawn.h"
//#include "queen.h"
//#include "rook.h"
#include <vector>

using std::vector;

#define WHITE 0
#define BLACK 1

const int SIDE = 664;

class Board {

	public:
		// Constructor
		Board();
		~Board();
		// Member Functions
		void play();
		void display(SDL_Renderer*, LTexture&, SDL_Rect[CLIPNUM]);
		void handleEvent( SDL_Event* );
	private:
		// Private Data Members
		vector<Piece*> pieces; // Chess Board

		// Private Helper Functions
};

Board::Board(){

  coord pos = {0,0};
/*  pieces.push_back(new Rook(pos,WHITE));
  pos[0]++;
  pieces.push_back(new Knight(pos,WHITE));
  pos[0]++;
  pieces.push_back(new Bishop(pos,WHITE));
  pos[0]++;
  pieces.push_back(new King(pos,WHITE));
  pos[0]++;
  pieces.push_back(new Queen(pos,WHITE));
  pos[0]++;
  pieces.push_back(new Bishop(pos,WHITE));
  pos[0]++;
  pieces.push_back(new Knight(pos,WHITE));
  pos[0]++;
  pieces.push_back(new Rook(pos,WHITE));

  pos[0] = 0; pos[1] = 7;
  pieces.push_back(new Rook(pos,BLACK));
  pos[0]++;
  pieces.push_back(new Knight(pos,BLACK));
  pos[0]++;
  pieces.push_back(new Bishop(pos,BLACK));
  pos[0]++;
  pieces.push_back(new King(pos,BLACK));
  pos[0]++;
  pieces.push_back(new Queen(pos,BLACK));
  pos[0]++;
  pieces.push_back(new Bishop(pos,BLACK));
  pos[0]++;
  pieces.push_back(new Knight(pos,BLACK));
  pos[0]++;
  pieces.push_back(new Rook(pos,BLACK));
*/
  for(int i = 0; i < 8; i++)
  {
    pos[0] = i; pos[1] = 1;
    pieces.push_back(new Pawn(pos,WHITE));
    pos[1] = 6;
    pieces.push_back(new Pawn(pos,BLACK));
  }
}

Board::~Board() {

  for(int i = 0; i < pieces.size(); i++)
    delete pieces[i];
}

void Board::handleEvent( SDL_Event* e ) {

  //mouse click  
  if( e->type == SDL_MOUSEBUTTONDOWN ) {
    
    //deselect all
    for(int i = 0; i < pieces.size(); i++)
      pieces[i]->deselect();

    //mouse location
    int x, y, gridX, gridY;
    SDL_GetMouseState( &x, &y );
    
    //find grid location of mouse
    for(int i = 1; i <= 8; i++)
      if( x < (SIDE/8)*i ) {
        gridX = i-1;
        break;
      }

    for(int i = 1; i <= 8; i++)
      if( y < (SIDE/8)*i ) {
        gridY = 8-i;
        break;
      }

    //find piece to select
    for(int i = 0; i < pieces.size(); i++) {
      if( (*pieces[i]->getPosition())[0] == gridX && 
          (*pieces[i]->getPosition())[1] == gridY ) {
        pieces[i]->select();
        break;
      }
    }
  }
}

void Board::display(SDL_Renderer* gRenderer, LTexture &texture, SDL_Rect clips[CLIPNUM]) {

  //Draw board
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
    {
      SDL_Rect fillRect = { SIDE/8*j, SIDE/8*i, SIDE/8*(j+1), SIDE/8*(i+1) };

      //Alternate gray and white
      if( (i+j)%2 )
        SDL_SetRenderDrawColor( gRenderer, 0x60, 0x60, 0x60, 0xFF );
      else
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

      SDL_RenderFillRect( gRenderer, &fillRect );
    }

  //display pieces
  for(int i = 0; i < pieces.size(); i++)
    pieces[i]->display( gRenderer, texture, clips, SIDE );

}

void Board::play() {

}

#endif
