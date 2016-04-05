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
		void display(SDL_Renderer*, LTexture&, SDL_Rect[CLIPNUM]);
		void handleEvent( SDL_Event* );
	private:
		// Private Data Members
		deque<Piece*> pieces; // Chess Board
		deque<coord> possMoves;
		int selectID;         // location of selected piece in deque
		bool turn = WHITE;

		// Private Helper Functions
};

Board::Board(){

  coord pos;
  pos.x = 0; pos.y = 0;
  pieces.push_back(new Rook(pos,WHITE));
  pos.x++;
  pieces.push_back(new Knight(pos,WHITE));
  pos.x++;
  pieces.push_back(new Bishop(pos,WHITE));
  pos.x++;
  pieces.push_back(new Queen(pos,WHITE));
  pos.x++;
  pieces.push_back(new King(pos,WHITE));
  pos.x++;
  pieces.push_back(new Bishop(pos,WHITE));
  pos.x++;
  pieces.push_back(new Knight(pos,WHITE));
  pos.x++;
  pieces.push_back(new Rook(pos,WHITE));

  pos.x = 0; pos.y = 7;
  pieces.push_back(new Rook(pos,BLACK));
  pos.x++;
  pieces.push_back(new Knight(pos,BLACK));
  pos.x++;
  pieces.push_back(new Bishop(pos,BLACK));
  pos.x++;
  pieces.push_back(new Queen(pos,BLACK));
  pos.x++;
  pieces.push_back(new King(pos,BLACK));
  pos.x++;
  pieces.push_back(new Bishop(pos,BLACK));
  pos.x++;
  pieces.push_back(new Knight(pos,BLACK));
  pos.x++;
  pieces.push_back(new Rook(pos,BLACK));

  for(int i = 0; i < 8; i++)
  {
    pos.x = i; pos.y = 1;
    pieces.push_back(new Pawn(pos,WHITE));
    pos.y = 6;
    pieces.push_back(new Pawn(pos,BLACK));
  }
}

Board::~Board() {

  for(int i = 0; i < pieces.size(); i++)
    delete pieces[i];
}

void Board::handleEvent( SDL_Event* e ) {

  //mouse click  
  if( e->type != SDL_MOUSEBUTTONDOWN )
    return;

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
    int possX = possMoves[i].x;
    int possY = possMoves[i].y;
    if( possX == gridX && possY == gridY ) {

      coord newPos;

      possMoves.clear();
      //castling
      if(pieces[selectID]->getType()==king )
        if( possX - pieces[selectID]->getPosition().x > 1 ) {
          for( int k = 0; k < pieces.size(); k++)
            if( pieces[k]->isLocated( possX + 1, possY )) {
              newPos.x = possX - 1;
              newPos.y = possY;
              pieces[k]->move(newPos);
            }
        }
        else if( possX - pieces[selectID]->getPosition().x < -1 ) {
          for( int k = 0; k < pieces.size(); k++)
            if( pieces[k]->isLocated( possX - 2, possY )) {
              newPos.x = possX + 1;
              newPos.y = possY;
              pieces[k]->move(newPos);
            }
        } 

      //move piece
      newPos.x = possX;
      newPos.y = possY;
      pieces[selectID]->move(newPos);

      //promote pawns
      if(pieces[selectID]->getType() == pawn && possY%7 == 0 ) {
        bool c = pieces[selectID]->getColor();
	delete pieces[selectID];
	pieces[selectID] = new Queen(newPos, c);
      }

      //check if captured piece
      for( int k = 0; k < pieces.size(); k++)
        if( pieces[k]->isLocated(possX, possY) && k != selectID ){
          delete pieces[k];
          pieces.erase(pieces.begin()+k);
          break;
        }

      turn = !turn;
      return;
    }
  }
    
  possMoves.clear();

  for(int i = 0; i < pieces.size(); i++) //find piece to select
    //if clicked on piece
    if( pieces[i]->isLocated(gridX, gridY) && pieces[i]->getColor() == turn) {
      if( pieces[i]->getSelected() ) {
        pieces[i]->deselect();
      }
      else {
        for(int i = 0; i < pieces.size(); i++) 
          pieces[i]->deselect();
        pieces[i]->select();
        possMoves = pieces[i]->getPossMoves( pieces );
        selectID = i;
      }
        
      return;
    }

  for(int i = 0; i < pieces.size(); i++) 
    pieces[i]->deselect();

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
    texture.render(gRenderer, SIDE/8*possMoves[i].x,
                   SIDE/8*7-SIDE/8*possMoves[i].y, &clips[13]); 

  //display selected piece so glow is in background
  for(int i = 0; i < pieces.size(); i++)
    if( pieces[i]->getSelected() )
      pieces[i]->display( gRenderer, texture, clips, SIDE );

  //display other pieces
  for(int i = 0; i < pieces.size(); i++)
    if( !pieces[i]->getSelected() )
      pieces[i]->display( gRenderer, texture, clips, SIDE );

}

#endif
