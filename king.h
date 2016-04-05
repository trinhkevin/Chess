// king.h
//
// Contains the King class

#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {

	public:
		King(coord, bool);
		virtual deque<coord> getPossMoves(deque<Piece*>);
	private:
};

King::King(coord nPosition, bool nColor) : Piece(king, nPosition, nColor) {
}

deque<coord> King::getPossMoves( deque<Piece*> pieces) {

	// Initialize Variables
        deque<coord> moves;
        coord ncoord;
        int x = getPosition().x;
        int y = getPosition().y;


	for(int i = 0; i < 9; i++)
          if( i != 4 ) {

            ncoord.x = x-1+i%3; ncoord.y = y-1+i/3;
            if( !checkSpace( ncoord, getColor(), pieces ) )
              moves.push_back(ncoord);
	  }

        //castling
	if( !getHasMoved() ) {
          //right side
          ncoord.x = x+1;
          ncoord.y = y;

          if(!checkSpace( ncoord, getColor(), pieces ) &&
             !checkSpace( ncoord, !getColor(), pieces) ) {

            ncoord.x++;
            if(!checkSpace( ncoord, getColor(), pieces ) &&
               !checkSpace( ncoord, !getColor(), pieces )) {

              for( int i = 0; i < pieces.size(); i++ )
                if(!pieces[i]->getHasMoved() && 
                    pieces[i]->getType()==rook &&
                    pieces[i]->isLocated(ncoord.x+1, ncoord.y))
                  moves.push_back(ncoord);
                  
            }

          }

          //left side
          ncoord.x = x-1;
          ncoord.y = y;

          if(!checkSpace( ncoord, getColor(), pieces ) &&
             !checkSpace( ncoord, !getColor(), pieces) ) {

            ncoord.x--;
            if(!checkSpace( ncoord, getColor(), pieces ) &&
               !checkSpace( ncoord, !getColor(), pieces )) {

              ncoord.x--;
              if(!checkSpace( ncoord, getColor(), pieces ) &&
                 !checkSpace( ncoord, !getColor(), pieces )) {

                for( int i = 0; i < pieces.size(); i++ )
                  if(!pieces[i]->getHasMoved() && 
                      pieces[i]->getType()==rook &&
                      pieces[i]->isLocated(ncoord.x-1, ncoord.y)) {
                    ncoord.x++;
                    moves.push_back(ncoord); 
                  }
              }
            }
          }
	}

	return moves;
}

#endif
