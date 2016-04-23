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
		bool noMoves();
        
	private:
		// Private Data Members
		deque<Piece*> pieces; // Chess Board
		deque<coord> possMoves;
		Piece* spaces[8][8];
		Piece* chosen = NULL; // selected piece
		Piece* enPass = NULL; //pawn that just moved two spaces
		Piece* lastKill = NULL;
		bool turn = WHITE;

		// Private Helper Functions
		void addPiece(Piece*);
		void movePiece(Piece*,coord,bool);
		void removePiece(Piece*);
		deque<coord> getPieceMoves(Piece*);
		bool checkCheck();
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

  coord pos = capturedPiece->getPosition();
  spaces[pos.x][pos.y] = NULL;

  // Hold piece
  lastKill = capturedPiece;

  //remove from deque
  for(int i = 0; i < pieces.size(); i++)
    if(pieces[i] == capturedPiece)
      pieces.erase(pieces.begin()+i);
}

deque<coord> Board::getPieceMoves(Piece* piece) {

  deque<coord> moves = piece->getPossMoves(spaces, enPass);
  coord pos = piece->getPosition();

  //look through possible moves
  for( int i = 0; i < moves.size(); i++ ) {

    bool castleRight = false, castleLeft = false;
    if(piece->getType()==king)
      if(moves[i].x-pos.x == 2 )
        castleRight = true;
      else if(moves[i].x-pos.x == -2 )
        castleLeft = true;

    //can't castle out of check
    if(checkCheck() &&(castleRight || castleLeft)) {
        moves.erase(moves.begin()+i);
        i--;
        continue;
    }

    //temporary move
    movePiece( piece, moves[i], true );

    if(checkCheck()) {
      moves.erase(moves.begin()+i);
      i--;
    }

    //reverse temp move
    piece->revert(spaces);

    //reverse castling
    if(castleRight)
      spaces[pos.x+1][pos.y]->revert(spaces);
    else if(castleLeft)
      spaces[pos.x-1][pos.y]->revert(spaces);

    //reverse capture
    if(lastKill)
      addPiece(lastKill);
    lastKill = NULL;
  }

  return moves;
}

bool Board::checkCheck() {

  //check enemy moves
  for( int j = 0; j < pieces.size(); j++ )
    if( pieces[j]->getColor() != turn ) {
      deque<coord> enemyMoves = pieces[j]->getPossMoves(spaces, enPass);

      for( int k = 0; k < enemyMoves.size(); k++ ) {
        Piece* target = spaces[enemyMoves[k].x][enemyMoves[k].y];

        //enemy can attack king
        if( target != NULL && target->getType() == king )
          return true;
      }
    }

  return false;

}

bool Board::noMoves() {

    for(int i = 0; i < pieces.size(); i++)
      if(pieces[i]->getColor()==turn)
        if( getPieceMoves(pieces[i]).size() > 0 )
          return false;

  return true;
}

void Board::movePiece(Piece* piece, coord moveTo, bool hypo) {
      
  // Castling
  if(piece->getType()==king && !piece->getHasMoved()) {
    coord rookPos = moveTo;
    rookPos.x--;

    // Right
    if(moveTo.x == 6)
      movePiece(spaces[moveTo.x+1][moveTo.y],rookPos,false);
 
    rookPos.x++;
    // Left
    if(moveTo.x == 2)
      movePiece(spaces[moveTo.x -2][moveTo.y],rookPos,false);
  }

  // Check if captured piece
  if(spaces[moveTo.x][moveTo.y] != NULL)
    removePiece(spaces[moveTo.x][moveTo.y]);

  if(piece->getType() == pawn) {

    // Check if Attacking en passant
    if(enPass != NULL && 
        enPass == spaces[moveTo.x][moveTo.y+1-enPass->getColor()*2])
      removePiece(enPass);

    // Check for new en passant if real move
    if(!hypo) {
      if(moveTo.y - piece->getPosition().y == 2 ||
          moveTo.y - piece->getPosition().y == -2)
        enPass = piece;
      else
        enPass = NULL;
    }
  }

  // Move piece
  piece->move(moveTo, spaces);
  
  // Promote pawns if real move
  if( !hypo && piece->getType() == pawn && moveTo.y%7 == 0) {
    bool c = piece->getColor();
    delete piece;
    piece = new Queen(moveTo, c);
  }
}
void Board::handleEvent(SDL_Event* e) {

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
    if(possMoves[i] == click)
      move = true;

  possMoves.clear();
 
  if(move) {

    //permanent move
    movePiece(chosen, click, false);

    //ignore last kill
    if(lastKill != NULL)
      delete lastKill;

    lastKill = NULL;

    // Change Turn
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
    possMoves = getPieceMoves(chosen);
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
 
  if(noMoves()) {
    if(checkCheck())
      texture.render(gRenderer, SIDE/8*4,
                   SIDE/8*7-SIDE/8*4, &clips[15+!turn]); 
    else
      texture.render(gRenderer, SIDE/8*4,
                   SIDE/8*7-SIDE/8*4, &clips[14]); 
  }
}

#endif
