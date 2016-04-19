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

    friend class AI;

	public:
		// Constructor
		Board();
		~Board();

		// Member Functions
		void display(SDL_Renderer*, LTexture&, SDL_Rect[CLIPNUM]);
		void handleEvent(SDL_Event*);
        
	private:
		// Private Data Members
		deque<Piece*> pieces; // Chess Board
		deque<coord> possMoves;
        Piece* spaces[8][8];
		Piece* chosen = NULL; // selected piece
		Piece* enPass = NULL; //pawn that just moved two spaces
		bool turn = WHITE;
        bool check = false;

		// Private Helper Functions
		void addPiece(Piece*);
		bool movePiece(Piece*,coord);
		void removePiece(Piece*);
		bool checkCheck(bool);
		bool checkCheckMate(bool);
};

Board::Board() {

  // Set Spaces to Null      
  for(int i = 0; i < 8; i++ )
    for(int j = 0; j < 8; j++ )
      spaces[i][j] = NULL;

  // Add Pieces to Board
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

  // Delete All Pieces  
  for(int i = 0; i < pieces.size(); i++)
    delete pieces[i];
}

void Board::addPiece(Piece* newPiece) {

  // Add Piece
  pieces.push_back(newPiece);
  spaces[newPiece->getPosition().x][newPiece->getPosition().y] = newPiece;

}

void Board::removePiece(Piece* capturedPiece) {

  // Delete Instance of Piece
  delete capturedPiece;
 
  for(int i = 0; i < pieces.size(); i++)
    if(pieces[i] == capturedPiece)
      pieces.erase(pieces.begin()+i);
}

bool Board::movePiece(Piece* piece, coord moveTo) {
      
  // Castling
  if(piece->getType()==king && !piece->getHasMoved()) {
    coord rookPos = moveTo;
    rookPos.x--;

    // Right
    if(moveTo.x == 6)
      movePiece(spaces[moveTo.x+1][moveTo.y],rookPos);
 
    rookPos.x++;
    // Left
    if(moveTo.x == 2)
      movePiece(spaces[moveTo.x -2][moveTo.y],rookPos);
  }

  // Check if captured piece
  if(spaces[moveTo.x][moveTo.y] != NULL)
    removePiece(spaces[moveTo.x][moveTo.y]);

  if(piece->getType() == pawn) {

    // Check if Attacking en passant
    if(enPass != NULL && 
        enPass == spaces[moveTo.x][moveTo.y+1-enPass->getColor()*2])
      removePiece(enPass);

    // Check for new en passant
    if(moveTo.y - piece->getPosition().y == 2 ||
        moveTo.y - piece->getPosition().y == -2)
      enPass = piece;
    else
      enPass = NULL;
  }

  // Move piece
  coord origPos = piece->getPosition();
  spaces[origPos.x][origPos.y] = NULL;
  piece->move(moveTo);
  spaces[moveTo.x][moveTo.y] = piece;
  
  // Prevent move into check...
  if (checkCheck(piece->getColor())) {
    spaces[moveTo.x][moveTo.y] = NULL;
    piece->move(origPos);
    spaces[origPos.x][origPos.y] = piece;
    return 0;
  }

  // Promote pawns
  if(piece->getType() == pawn && moveTo.y%7 == 0) {
    bool c = piece->getColor();
    delete piece;
    piece = new Queen(moveTo, c);
  }

  return 1;
}

void Board::handleEvent(SDL_Event* e) {

  // Mouse Click  
  if(e->type != SDL_MOUSEBUTTONDOWN)
    return;

  // Mouse Location
  coord click;
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  // Find grid location of mouse
  for(int i = 1; i <= 8; i++)
    if(mouseX < (SIDE/8)*i) {
      click.x = i-1;
      break;
    }

  for(int i = 1; i <= 8; i++)
    if(mouseY < (SIDE/8)*i) {
      click.y = 8-i;
      break;
    }

  // Check if user chose to move

  // Look through possible moves
  bool move = false;
  for(int i = 0; i < possMoves.size(); i++)
    if(possMoves[i].x == click.x && possMoves[i].y == click.y)
      move = true;

  possMoves.clear();
  
  if(move) {
 
    // If Move Was Successful, Change Turn
    if(movePiece(chosen,click))
        turn = !turn;
    
    // Deselect
    chosen = NULL;

    return;
  }
    
  // Clicked empty or opponent space
  if(spaces[click.x][click.y] == NULL)
    chosen = NULL;
  else if(spaces[click.x][click.y] == chosen ||  // Clicked selected piece
           spaces[click.x][click.y]->getColor() != turn)
    chosen = NULL;
  else {                                          // Selected new piece
    chosen = spaces[click.x][click.y];
    possMoves = chosen->getPossMoves(spaces, enPass);
  }
}

void Board::display(SDL_Renderer* gRenderer, LTexture &texture, SDL_Rect clips[CLIPNUM]) {

  // Draw board
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
    {
      SDL_Rect fillRect = { SIDE/8*j, SIDE/8*i, SIDE/8*(j+1), SIDE/8*(i+1) };

      // Alternate gray and white
      if( (i+j)%2 )
        SDL_SetRenderDrawColor( gRenderer, 0x60, 0x60, 0x60, 0xFF );
      else
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

      SDL_RenderFillRect( gRenderer, &fillRect );
    }
  
  // Show possible moves
  for(int i = 0; i < possMoves.size(); i++)
    texture.render(gRenderer, SIDE/8*possMoves[i].x,
                   SIDE/8*7-SIDE/8*possMoves[i].y, &clips[13]); 

  // Show selected glow
  if(chosen != NULL )
    texture.render(gRenderer, SIDE/8*chosen->getPosition().x,
                   SIDE/8*7-SIDE/8*chosen->getPosition().y, &clips[12]); 

  // Display pieces
  for(int i = 0; i < pieces.size(); i++)
    pieces[i]->display( gRenderer, texture, clips, SIDE );

}

bool Board::checkCheck(bool color) {
  
    // Find location of king
    int i, j;
    coord LocK;
    
    for (i = 0; i < pieces.size(); i++) {
        if (pieces[i]->getType() == king && pieces[i]->getColor() == color) {
            LocK = pieces[i]->getPosition();
        }
    }
  
    // See if this matches any possible moves from other team
    deque<coord> tempPossMoves;
    for (i = 0; i < pieces.size(); i++) {
        if (pieces[i]->getColor() != color) {
            for (j = 0; j < pieces[i]->getPossMoves(spaces, enPass).size(); j++) {
	            if (pieces[i]->getPossMoves(spaces, enPass)[j] == LocK)
	                return 1;
            }
        }
    }

    return 0;
}

/*
bool Board::checkCheckmate(bool color) {
        if(checkCheck(color)) {
                for(int i = 0; i < pieces.size(); i++) {
                        if(pieces[i]->getColor() != color) {
                                for(int j = 0; j < pieces[i]->getPossMoves(spaces, enPass).size(); j++) {
                                        if(move)
                                }        
                        }
                }
        }
}*/

#endif
