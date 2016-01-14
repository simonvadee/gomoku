#include "IA.hh"

extern Pos _dir[4];

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player), _recursionNumber(10)
{

}

IA::~IA()
{

}

<<<<<<< HEAD
int		IA::isFriendAligned(Pos& pos, Pos& dir)
{
  for (int i = 0; i < 5; ++i)
    {
      
    }
}

int		IA::checkDirection(Pos& pos, Pos& dir)
{
  return (isFriendAligned(pos, dir));
=======
int		IA::findPossibleMoves(Pos pos, Pos* possibleMoves)
{
  // push all possible moves in possibleMoves
  return 0;
>>>>>>> ed65ad63fcfb8e8281c08fb871d9f58f731c35e1
}

int		IA::megaval(Pos& pos)
{
<<<<<<< HEAD
  Pos		inversDir;
  int		weight = 0;

  for (unsigned int i = 0; i < 4; ++i)
    {
      inversDir.x = -_dir[i].x;
      inversDir.y = -_dir[i].y;
      weight += checkDirection(pos, _dir[i]) + checkDirection(pos, inversDir);
    }  
=======
  // int		weight = 0;

  // for (unsigned int i = 0; i < 4; ++i)
  //   {
  //     inversDir.x = -_dir[i].x;
  //     inversDir.y = -_dir[i].y;
  //     weight += checkDirection() + checkDirection();
  //   }
>>>>>>> ed65ad63fcfb8e8281c08fb871d9f58f731c35e1
}

int		IA::negamax(Pos pos, int depth, int alpha, int beta)
{
  int		best, value;
  Pos		*possibleMoves;

  if (depth == _recursionNumber)
    return megaval(pos);

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
