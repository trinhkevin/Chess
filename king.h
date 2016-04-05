// king.h
//
// Contains the King class

#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {

	public:
		King(coord, bool);
	        virtual deque<coord> getPossMoves( Piece* [8][8] );
	private:
};

King::King(coord nPosition, bool nColor) : Piece(king, nPosition, nColor) {
}

deque<coord> King::getPossMoves( Piece* spaces[8][8]) {

	// Initialize Variables
        deque<coord> moves;
        coord ncoord;
        int x = getPosition().x;
        int y = getPosition().y;


	for(int i = 0; i < 9; i++)
          if( i != 4 ) {

            ncoord.x = x-1+i%3; ncoord.y = y-1+i/3;
            //on board
            if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8)
              if( spaces[ncoord.x][ncoord.y] ==NULL ||
                  spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
                moves.push_back(ncoord);
	  }

        //castling
	if( !getHasMoved() ) {
          //right side
          ncoord.x = x+2;
          ncoord.y = y;

          if(spaces[ncoord.x-1][ncoord.y] == NULL &&
             spaces[ncoord.x][ncoord.y] == NULL   &&
             spaces[ncoord.x+1][ncoord.y] != NULL &&
            !spaces[ncoord.x+1][ncoord.y]->getHasMoved())
            moves.push_back(ncoord);

          //left side
          ncoord.x = x-2;
          ncoord.y = y;

          if(spaces[ncoord.x+1][ncoord.y] == NULL &&
             spaces[ncoord.x][ncoord.y] == NULL   &&
             spaces[ncoord.x-1][ncoord.y] == NULL   &&
             spaces[ncoord.x-2][ncoord.y] != NULL &&
            !spaces[ncoord.x-2][ncoord.y]->getHasMoved())
            moves.push_back(ncoord);
	}

	return moves;
}

#endif
