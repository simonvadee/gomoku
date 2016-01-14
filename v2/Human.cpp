#include "Human.hh"

Human::Human(Board *board, Gui *gui, PLAYER player): Player(board, gui, player)
{

}

Human::~Human()
{

}

bool		Human::play()
{
  while (!_board->move(_gui->gameListener(), _id));
  _gui->updateDisplay();
}
