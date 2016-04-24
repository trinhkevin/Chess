#ifndef AI_H
#define AI_H

#include "board.h"

class AI {

  public:
    AI(char);
    void tryMove(Board&); 
  private:
    bool color = BLACK;

};

AI::AI(char opponentColor) {

  if( opponentColor == 'b' )
    color = WHITE;
}

void AI::tryMove(Board& board)
{
  //not cpu turn
  if(board.turn != color)
    return;

  deque<coord> moves;

  int i = 0;

  // skip opponent pieces or pieces that can't move
  while(board.pieces[i]->getColor() != color ||
        !board.getPieceMoves(board.pieces[i]).size())
    i++;

  // make first possible move
  board.movePiece(board.pieces[i],
                  board.getPieceMoves(board.pieces[i])[0], false);
   
}

#endif
