#include <iostream>
#include "Board.hh"
#include "Gui.hh"

bool		isNumber(char *number)
{
  for (int i = 0; number[i] != 0; ++i)
    if (!isdigit(number[i]))
      return false;
  return true;
}

void			startGame(int size)
{
  Gui* gui = new Gui();
}

int			main(int ac, char **av)
{
  if (ac != 2)
    std::cout << "Incorrect number of args, try ./gomoku size" << std::endl;
  else if (!isNumber(av[1]))
    std::cout << "Incorrect number of args, try ./gomoku size[int]" << std::endl;
  else
    startGame(std::atoi(av[1]));
}
