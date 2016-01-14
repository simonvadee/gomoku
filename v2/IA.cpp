#include "IA.hh"

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player), _recursionNumber(10)
{

}

IA::~IA()
{

}

Pos		IA::negamax(Pos pos, int depth, int alpha, int beta)
{
  Pos		best;
  return best;
}

bool		IA::play()
{
  Pos		pos;

  pos.x = 0;
  pos.y = 0;
  _board->move(this->negamax(pos, _recursionNumber, MININT, MAXINT), _id);
  _gui->updateDisplay();
}
