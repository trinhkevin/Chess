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
#include <deque>

using std::deque;

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
		deque<Piece*> pieces; // Chess Board
		deque<coord*> possMoves;
		int selectID;         // location of selected piece in deque

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

    //check if user chose to move
    //look through possible moves
    for(int i = 0; i < possMoves.size(); i++) {
      int possX = (*possMoves[i])[0];
      int possY = (*possMoves[i])[1];
      if( possX == gridX && possY == gridY ) {
        //move piece
        coord newPos = { possX, possY };
        pieces[selectID]->move(newPos);
        for(int k = 0; k < possMoves.size(); k++)
          delete[] possMoves[k];
        possMoves.clear();

        //check if captured piece
        for( int k = 0; k < pieces.size(); k++)
          if( (*pieces[k]->getPosition())[0] == possX &&
              (*pieces[k]->getPosition())[1] == possY &&
                selectID != k ) {
            delete pieces[k];
            pieces.erase(pieces.begin()+k);
            break;
          }

        return;
      }
    }
    
    for(int i = 0; i < possMoves.size(); i++)
      delete[] possMoves[i];

    possMoves.clear();

    //deselect all
    for(int i = 0; i < pieces.size(); i++)
      pieces[i]->deselect();

    //find piece to select
    for(int i = 0; i < pieces.size(); i++) {
      if( (*pieces[i]->getPosition())[0] == gridX && 
          (*pieces[i]->getPosition())[1] == gridY ) {
        pieces[i]->select();
	possMoves = pieces[i]->findPossMoves( pieces );
	selectID = i;
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
  
  //show possible moves
  for(int i = 0; i < possMoves.size(); i++)
    texture.render(gRenderer, SIDE/8*((*possMoves[i])[0]),
                   SIDE/8*7-SIDE/8*((*possMoves[i])[1]), &clips[13]); 

  //display selected piece so glow is in background
  for(int i = 0; i < pieces.size(); i++)
    if( pieces[i]->getSelected() )
      pieces[i]->display( gRenderer, texture, clips, SIDE );

  //display other pieces
  for(int i = 0; i < pieces.size(); i++)
    if( !pieces[i]->getSelected() )
      pieces[i]->display( gRenderer, texture, clips, SIDE );

}

void Board::play() {

}

#endif
