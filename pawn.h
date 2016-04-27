// pawn.h
//
// Prototype for Pawn class

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
    public:
	Pawn(coord, bool );
	virtual deque<coord> getPossMoves( Piece*[8][8], Piece* );
    private:
};

Pawn::Pawn(coord nPosition, bool nColor )
    : Piece(pawn, nPosition, nColor ) {
}

deque<coord> Pawn::getPossMoves( Piece* spaces[8][8], Piece* enPass ){
        //deque will contain all locations that the pawn can move to
  
	// Initialize Variables
	deque<coord> moves;

  if(getType()==queen) {
	  scan( -1,  0, 7, moves, spaces );
		scan( -1,  1, 7, moves, spaces );
	  scan(  0,  1, 7, moves, spaces );
	  scan(  1,  1, 7, moves, spaces );
		scan(  1,  0, 7, moves, spaces );
		scan(  1, -1, 7, moves, spaces );
	  scan(  0, -1, 7, moves, spaces );
  	scan( -1, -1, 7, moves, spaces );

  	return moves;
  }

	coord ncoord;
	int x = getPosition().x;
	int y = getPosition().y;

	// Compute Moves
	ncoord.x = x; ncoord.y = y+1-getColor()*2;
        
	// one space ahead	  
        if( spaces[ncoord.x][ncoord.y] == NULL ) {
          moves.push_back(ncoord);
          //two spaces ahead
	  ncoord.y = y+2-getColor()*4;
	  if(!getHasMoved()&&spaces[ncoord.x][ncoord.y] == NULL )
            moves.push_back(ncoord);
	}

	// forward left
	ncoord.x = x-1; ncoord.y = y+1-getColor()*2;
	if( x > 0 )
          if( spaces[ncoord.x][ncoord.y] != NULL && 
              spaces[ncoord.x][ncoord.y]->getColor() != getColor())
	    moves.push_back(ncoord);
          else if( enPass != NULL && // check for enPassant attack
                   spaces[ncoord.x][ncoord.y+1-enPass->getColor()*2] == enPass)
	    moves.push_back(ncoord);

        // forward right
	ncoord.x = x+1;
	if( x < 7 )
          if( spaces[ncoord.x][ncoord.y] != NULL && 
              spaces[ncoord.x][ncoord.y]->getColor() != getColor())
	    moves.push_back(ncoord);
          else if( enPass != NULL &&  // check for enPassant attack
                   spaces[ncoord.x][ncoord.y+1-enPass->getColor()*2] == enPass)
	    moves.push_back(ncoord);

	return moves;
}

#endif
