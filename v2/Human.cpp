#include "Human.hh"

Human::Human(Board *board, Gui *gui): Player(board, gui)
{

}

Human::~Human()
{

}

bool		Human::play()
{
  std::cout << "inside play" << std::endl;
  while (!_board->move(_gui->gameListener(), PLAYER1))
    std::cout << "false" << std::endl;
  std::cout << "true" << std::endl;
  _gui->updateDisplay();
}
