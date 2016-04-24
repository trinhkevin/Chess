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

  printf("turn\n");

  board.turn = !board.turn;
}


#endif
