#include "IA.hh"

extern Pos _dir[4];

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player), _recursionNumber(10)
{

}

IA::~IA()
{

}

int		IA::isFriendAligned(Pos& pos, Pos& dir)
{
  for (int i = 0; i < 5; ++i)
    {
      
    }
}

int		IA::checkDirection(Pos& pos, Pos& dir)
{
  return (isFriendAligned(pos, dir));
}

int		IA::megaval(Pos& pos)
{
  Pos		inversDir;
  int		weight = 0;

  for (unsigned int i = 0; i < 4; ++i)
    {
      inversDir.x = -_dir[i].x;
      inversDir.y = -_dir[i].y;
      weight += checkDirection(pos, _dir[i]) + checkDirection(pos, inversDir);
    }  
}

Pos		IA::negamax(Pos pos, int depth, int alpha, int beta)
{
  Pos		best;

  // if (depth == _recursionNumber)
  //   return eval(pos);

  return best;
}

bool		IA::play()
{
  Pos		pos;

  pos.x = 0;
  pos.y = 0;
  _board->move(this->negamax(pos, 0, MININT, MAXINT), _id);
  _gui->updateDisplay();
}
