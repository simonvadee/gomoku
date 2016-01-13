# include "Gui.hh"
# include "Board.hh"
# include "IA.hh"
# include "Human.hh"

#define CHANGE_TURN(x) (3 - x)

bool		isNumber(char *number)
{
  for (int i = 0; number[i] != 0; ++i)
    if (!isdigit(number[i]))
      return false;
  return true;
}

void		launchGame(Board *board, Player *pl1, Player *pl2, Gui *gui)
{
  PLAYER	turn = PLAYER1;

  while (true)
    {
      pl1->play();
      
      if (board->isWinner())
	std::cout << "PLAYER 1 WINS !" << std::endl;

      pl2->play();
      if (board->isWinner())
	std::cout << "PLAYER 1 WINS !" << std::endl;
    }
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
  // Options *options;
  Gui *gui = new Gui();
  // options = gui->menu();
  // Board *board = new Board(options->size, options->rules);
  Board *board = new Board(19);
  gui->setBoard(board);
  gui->updateDisplay();
  launchGame(board, new Human(board, gui), new IA(board, gui), gui);
  return 0;
}
