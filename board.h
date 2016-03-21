// board.h
//
// Contains the Board class

#ifndef BOARD_H
#define BOARD_H

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include <vector>

#define WHITE 0
#define BLACK 1

class Board {

	public:
		// Constructor
		Board();

		// Member Functions
		void play();
	private:
		// Private Data Members
		vector< vector<Piece> > Board; // Chess Board

		// Private Helper Functions
};

Board::Board() {
	
}


#endif
