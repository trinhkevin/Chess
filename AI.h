#ifndef AI_H
#define AI_H

#include "board.h"

class AI {

  public:
    AI(char, Board*);
    void lookAhead(int,Piece*,coord*,Piece**,coord*,int*,bool);
    Piece* tryMove(int,bool);
    int score();
  private:
    bool color = BLACK;
    Board* board;
};

AI::AI(char opponentColor, Board* chessBoard) {

  if( opponentColor == 'b' )
    color = WHITE;

  board = chessBoard;
}

Piece* AI::tryMove(int turns, bool hypo)
{
  //not cpu turn
  if(board->turn != color)
    return NULL;

  Piece* bestPiece = NULL;
  coord bestMove;
  int bestScore;
	
  lookAhead(turns, NULL, NULL, &bestPiece,&bestMove,&bestScore, true);

  // make best move
  board->movePiece(bestPiece,bestMove,hypo);

  return bestPiece;   
}

void AI::lookAhead(int turns, Piece* candidateP, coord* candidateM, 
                   Piece** bestP, coord* bestM, int* bestS, bool first) {

  for(int i = 0; i < 64; i++) {

    Piece* piece = board->spaces[i%8][i/8];
		if(first)
			candidateP = piece;

    if(piece && piece->getColor() == color) {

      deque<coord> moves = board->getPieceMoves(piece);
      for(int j = 0; j < moves.size(); j++) {
				if(first)
					candidateM = &moves[j];

				Piece* enPass = board->enPass;
        board->movePiece(piece,moves[j],true);
        Piece* hold = board->hold;

				if(!*bestP) {
          *bestS = -10000;
          *bestP = candidateP;
          *bestM = *candidateM;
				}
        else if (turns == 0 && score() > *bestS)  {
          *bestS = score();
          *bestP = candidateP;
          *bestM = *candidateM;
        }
				//endgame
				if(board->noMoves(!board->turn)) {
					//checkmate
					if(board->checkCheck(!board->turn)){
          	*bestS = 10000;
          	*bestP = candidateP;
          	*bestM = *candidateM;
					}
					else if( -1 > *bestS ) {   //draw
          	*bestS = -1;
          	*bestP = candidateP;
          	*bestM = *candidateM;
					}
        }
				else if(turns > 0) {

          // predict opponent move
          board->turn = !board->turn;
          color = !color;
					Piece* oppEnPass = board->enPass;
          Piece* oppPiece = tryMove(turns-1,true);
					Piece* oppHold = board->hold;
          color = !color;
          board->turn = !board->turn;
          
          lookAhead(turns-1,candidateP,candidateM,bestP,bestM,bestS,false);

					oppPiece->revert(board->spaces);
					board->enPass = oppEnPass;
					if(oppHold)
						board->addPiece(oppHold);
        }

        piece->revert(board->spaces);

				board->enPass = enPass;
        if(hold)
          board->addPiece(hold);
        hold = NULL;
      }     
    }
  }

}

int AI::score()
{
  int points = 0;

	if(board->checkCheck(!board->turn))
		points += 50;

  for(int i = 0; i < board->pieces.size(); i++) {
    int value;
    switch(board->pieces[i]->getType()) {
      case pawn:   value = 100; break;
      case bishop: value = 300; break;
      case knight: value = 300; break;
      case rook:   value = 500; break;
      case queen:  value = 900; break;
      case king:   value = 0; break;
    }
    if(board->pieces[i]->getColor() == color) {
      points += value;
			if(color==WHITE)
				points += board->pieces[i]->getPosition().y;
			else
				points += 7-board->pieces[i]->getPosition().y;
		}
    else
      points -= value;
  }

  return points; 
}

#endif
