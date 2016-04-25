#ifndef AI_H
#define AI_H

#include "board.h"

class AI {

  public:
    AI(char, Board*);
    int lookAhead(int);
    void tryMove(int);
    int score();
  private:
    bool color = BLACK;
    Board* board;
    Piece* bestPiece;
    coord bestMove;
    int bestScore;
};

AI::AI(char opponentColor, Board* chessBoard) {

  if( opponentColor == 'b' )
    color = WHITE;

  board = chessBoard;
}

void AI::tryMove(int turns)
{
  //not cpu turn
  if(board->turn != color)
    return;

  bestScore = -500;
  lookAhead(turns);

  // make best move
  board->movePiece(bestPiece,bestMove,false);
  
}

int AI::lookAhead(int turns) {

  for(int i = 0; i < 64; i++) {

    Piece* piece = board->spaces[i%8][i/8];

    if(piece && piece->getColor() == color) {

      deque<coord> moves = board->getPieceMoves(piece);
      for(int j = 0; j < moves.size(); j++) {
        board->movePiece(piece,moves[j],true);
        Piece* hold = board->hold;

        if(turns == 0 && score() > bestScore) {
          bestScore = score();
          bestPiece = piece;
          bestMove = moves[j];
        }
        else if(turns > 0) {

          // predict opponent move
          board->turn = !board->turn;
          color = !color;
          tryMove(turns-1);
          color = !color;
          board->turn = !board->turn;
          
          lookAhead(turns-1);
        }

        piece->revert(board->spaces);

        if(hold)
          board->addPiece(hold);
        hold = NULL;
      }     
    }
  }

}

int AI::score()
{
  board->turn = !board->turn;

  if(board->noMoves()) {
    //checkmate
    if( board->checkCheck()) {
      board->turn = !board->turn;
      return 100;
    }

    //avoid draw
    board->turn = !board->turn;
    return -100;
  }
  board->turn = !board->turn;


  int points = 0;

  for(int i = 0; i < board->pieces.size(); i++) {
    int value;
    switch(board->pieces[i]->getType()) {
      case pawn:   value = 1; break;
      case bishop: value = 3; break;
      case knight: value = 3; break;
      case rook:   value = 5; break;
      case queen:  value = 9; break;
      case king:   value = 0; break;
    }
    if(board->pieces[i]->getColor() == color) 
      points += value;
    else
      points -= value;
  }

  return points; 
}

#endif
