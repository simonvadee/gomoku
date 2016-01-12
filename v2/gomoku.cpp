# include "Gui.hh"
# include "Board.hh"
# include "IA.hh"
# include "Human.hh"

#define CHANGE_TURN(x) (3 - x)

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

int		main()
{
  Board board = new Board(19);
  Gui gui = new Gui(board, 19);
  launchGame(board, new Human(board, gui), new IA(board, gui));
}
