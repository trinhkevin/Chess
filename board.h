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
                Piece* spaces[8][8];
		Piece* chosen = NULL; // selected piece
		bool turn = WHITE;

		// Private Helper Functions
		void addPiece(Piece*);
		void movePiece(Piece*,coord);
		void removePiece(Piece*);
};

Board::Board(){

  for(int i = 0; i < 8; i++ )
    for(int j = 0; j < 8; j++ )
      spaces[i][j] = NULL;

  coord pos;
  pos.x = 0; pos.y = 0;
  addPiece(new Rook(pos,WHITE));
  pos.x++;
  addPiece(new Knight(pos,WHITE));
  pos.x++;
  addPiece(new Bishop(pos,WHITE));
  pos.x++;
  addPiece(new Queen(pos,WHITE));
  pos.x++;
  addPiece(new King(pos,WHITE));
  pos.x++;
  addPiece(new Bishop(pos,WHITE));
  pos.x++;
  addPiece(new Knight(pos,WHITE));
  pos.x++;
  addPiece(new Rook(pos,WHITE));

  pos.x = 0; pos.y = 7;
  addPiece(new Rook(pos,BLACK));
  pos.x++;
  addPiece(new Knight(pos,BLACK));
  pos.x++;
  addPiece(new Bishop(pos,BLACK));
  pos.x++;
  addPiece(new Queen(pos,BLACK));
  pos.x++;
  addPiece(new King(pos,BLACK));
  pos.x++;
  addPiece(new Bishop(pos,BLACK));
  pos.x++;
  addPiece(new Knight(pos,BLACK));
  pos.x++;
  addPiece(new Rook(pos,BLACK));

  for(int i = 0; i < 8; i++)
  {
    pos.x = i; pos.y = 1;
    addPiece(new Pawn(pos,WHITE ));
    pos.y = 6;
    addPiece(new Pawn(pos,BLACK ));
  }
}

Board::~Board() {

  for(int i = 0; i < pieces.size(); i++)
    delete pieces[i];
}

void Board::addPiece( Piece* newPiece ) {

  pieces.push_back(newPiece);
  spaces[newPiece->getPosition().x][newPiece->getPosition().y] = newPiece;

}

void Board::removePiece( Piece* capturedPiece ) {

  delete capturedPiece;

  for(int i = 0; i < pieces.size(); i++)
    if(pieces[i] == capturedPiece)
      pieces.erase(pieces.begin()+i);
}

void Board::movePiece( Piece* piece, coord moveTo ) {

  //castling
  if(piece->getType()==king && !piece->getHasMoved()) {
    coord rookPos = moveTo;
    rookPos.x--;
    //right
    if( moveTo.x == 6 )
      movePiece(spaces[moveTo.x+1][moveTo.y],rookPos);
 
    rookPos.x++;
    //left
    if( moveTo.x == 2 )
      movePiece(spaces[moveTo.x -2][moveTo.y],rookPos);
  }

  //check if captured piece
  if( spaces[moveTo.x][moveTo.y] != NULL )
    removePiece( spaces[moveTo.x][moveTo.y] );

  //move piece
  spaces[piece->getPosition().x][piece->getPosition().y] = NULL;
  piece->move(moveTo);
  spaces[moveTo.x][moveTo.y] = piece;

  //promote pawns
  if(piece->getType() == pawn && moveTo.y%7 == 0 ) {
    bool c = piece->getColor();
    delete piece;
    piece = new Queen(moveTo, c);
  }
}

void Board::handleEvent( SDL_Event* e ) {

  //mouse click  
  if( e->type != SDL_MOUSEBUTTONDOWN )
    return;

  //mouse location
  coord click;
  int mouseX, mouseY;
  SDL_GetMouseState( &mouseX, &mouseY );

  //find grid location of mouse
  for(int i = 1; i <= 8; i++)
    if( mouseX < (SIDE/8)*i ) {
      click.x = i-1;
      break;
    }

  for(int i = 1; i <= 8; i++)
    if( mouseY < (SIDE/8)*i ) {
      click.y = 8-i;
      break;
    }

  //check if user chose to move

  //look through possible moves
  bool move = false;

  for(int i = 0; i < possMoves.size(); i++)
    if( possMoves[i].x == click.x && possMoves[i].y == click.y )
      move = true;

  possMoves.clear();
  
  if(move) {
 
    movePiece(chosen,click);

    //deselect
    chosen = NULL;

    //next turn
    turn = !turn;
    return;
  }
    
  //clicked empty or opponent space
  if( spaces[click.x][click.y] == NULL )
    chosen = NULL;
  else if( spaces[click.x][click.y] == chosen ||  //clicked selected piece
           spaces[click.x][click.y]->getColor() != turn )
    chosen = NULL;
  else {                                          //selected new piece
    chosen = spaces[click.x][click.y];
    possMoves = chosen->getPossMoves( spaces );
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
    texture.render(gRenderer, SIDE/8*possMoves[i].x,
                   SIDE/8*7-SIDE/8*possMoves[i].y, &clips[13]); 

  if(chosen != NULL )
    texture.render(gRenderer, SIDE/8*chosen->getPosition().x,
                   SIDE/8*7-SIDE/8*chosen->getPosition().y, &clips[12]); 

  //display other pieces
  for(int i = 0; i < pieces.size(); i++)
    pieces[i]->display( gRenderer, texture, clips, SIDE );

}

#endif
