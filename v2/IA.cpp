#include "IA.hh"

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player), _recursionNumber(10)
{

}

IA::~IA()
{

}

Pos		IA::minmax()
{

}

bool		IA::play()
{
  _board->move(this->minmax(), _id);
  _gui->updateDisplay();
}
