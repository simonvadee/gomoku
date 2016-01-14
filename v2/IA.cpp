#include "IA.hh"

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player), _recursionNumber(10)
{

}

IA::~IA()
{

}

int		IA::findPossibleMoves(Pos pos, Pos* possibleMoves)
{
  // push all possible moves in possibleMoves
  return 0;
}


int		IA::negamax(Pos pos, int depth, int alpha, int beta)
{
  int		best, value;
  Pos		*possibleMoves;

  if (depth == _recursionNumber)
    return eval(pos);

  best = -MAXINT;
  for (unsigned int i = 0; i < findPossibleMoves(pos, possibleMoves); ++i)
    {
      value = -negamax(possibleMoves[i], depth + 1, -beta, -alpha);
      if (value > best)
	{
	  best = value;
	  if (best > alpha)
	    {
	      alpha = best;
	      if (alpha > beta)
		return best;
	    }
	}
    }
  return best;
}



bool		IA::play()
{
  Pos		pos;
  int		best, value = 0;
  Pos		*possibleMoves;

  for (unsigned int i = 0; i < findPossibleMoves(pos, possibleMoves); ++i)
    {
      value = negamax(possibleMoves[i], 0, -MAXINT, MAXINT);
      if (value > best)
	{
	  best = value;
	  pos = possibleMoves[i];
	}
    }
  _board->move(pos, _id);
  _gui->updateDisplay();
}
