#ifndef AI_H
#define AI_H

#include "board.h"

class AI {

  public:
    AI(char, Board*);
		//recursive look
    void lookAhead(int,Piece*,coord*,Piece**,coord*,int*,bool);
    Piece* tryMove(int,bool);
		//return value of current board state
    int score();
  private:
    bool color = BLACK;  //team color
    Board* board;        //bound chessboard
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

  //track favorite piece/move
  Piece* bestPiece = NULL;
  coord bestMove;
  int bestScore = -11000;
	
  lookAhead(turns, NULL, NULL, &bestPiece,&bestMove,&bestScore, true);

  // make best move
  board->movePiece(bestPiece,bestMove,hypo);

  return bestPiece;   
}

void AI::lookAhead(int turns, Piece* candidateP, coord* candidateM, 
                   Piece** bestP, coord* bestM, int* bestS, bool first) {

	//look through spaces
  for(int i = 0; i < 64; i++) {

    Piece* piece = board->spaces[i%8][i/8];

		//find own pieces
    if(piece && piece->getColor() == color) {
		
			//track root piece
			if(first)
				candidateP = piece;

			//check through moves
      deque<coord> moves =  board->getPieceMoves(piece);

      for(int j = 0; j < moves.size(); j++) {
				//track root move
				if(first)
					candidateM = &moves[j];

				//temporary move
				Piece* enPass = board->enPass;
        board->movePiece(piece,moves[j],true);
        Piece* hold = board->hold;

				//check score if end of recursion
        if (turns == 0 && score() > *bestS)  {
          *bestS = score();
          *bestP = candidateP;
          *bestM = *candidateM;
        }
				//endgame
				if(board->noMoves(!board->turn)) {
					//checkmate
					if(board->checkCheck(!board->turn) && 10000 > *bestS){
          	*bestS = 9000;
						//quick checkmate most valuable
						if(first)
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

					// pick dead end move only if no options
					if(board->noMoves(color) && -10000 > *bestS) {
          	*bestS = -10000;
          	*bestP = candidateP;
          	*bestM = *candidateM;
					}					
					else
          	lookAhead(turns-1,candidateP,candidateM,bestP,bestM,bestS,false);

					//revert opponent move
					oppPiece->revert(board->spaces);
					board->enPass = oppEnPass;
					if(oppHold)
						board->addPiece(oppHold);
        }

				//revert own move
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

	// putting opponent in check is good
	if(board->checkCheck(!color))
		points += 50;

  for(int i = 0; i < board->pieces.size(); i++) {
    int value;
		//piece values
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
			// prefer forward positioning
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
