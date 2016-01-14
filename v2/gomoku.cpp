# include "GameCore.hh"

bool		isNumber(char *number)
{
  for (int i = 0; number[i] != 0; ++i)
    if (!isdigit(number[i]))
      return false;
  return true;
}

int		main(int ac, char **av)
{
  if (ac != 2)
    {
      std::cerr << "Incorrect number of args, try ./gomoku size" << std::endl;
      return 1;
    }
  else if (!isNumber(av[1]))
    {
      std::cerr << "Incorrect number of args, try ./gomoku size[int]" << std::endl;
      return 1;
    }

  GameCore*	game = new GameCore();

  return 0;
}
