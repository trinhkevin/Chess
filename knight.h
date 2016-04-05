// knight.h
//
// Contains the Knight class

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {

	public:
		Knight(coord, bool);
	        virtual deque<coord> getPossMoves( Piece*[8][8] );
	private:
};

Knight::Knight(coord nPosition, bool nColor) : Piece(knight, nPosition, nColor) {
}

deque<coord> Knight::getPossMoves( Piece* spaces[8][8]) {

	// Initialize Variables
        deque<coord> moves;
        coord ncoord;
	int x = getPosition().x;
	int y = getPosition().y;

        ncoord.x = x-1; ncoord.y = y-2;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        ncoord.x = x-2; ncoord.y = y-1;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        ncoord.x = x-2; ncoord.y = y+1;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        ncoord.x = x-1; ncoord.y = y+2;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        ncoord.x = x+1; ncoord.y = y+2;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        ncoord.x = x+2; ncoord.y = y+1;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        ncoord.x = x+2; ncoord.y = y-1;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        ncoord.x = x+1; ncoord.y = y-2;
	if( ncoord.x >= 0 && ncoord.x < 8 && ncoord.y >= 0 && ncoord.y < 8 )
	  if( spaces[ncoord.x][ncoord.y] == NULL ||
              spaces[ncoord.x][ncoord.y]->getColor() != getColor() )
            moves.push_back(ncoord);

        return moves;

}

#endif
