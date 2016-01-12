# include "Board.hh"
# include "IA.hh"
# include "Human.hh"

void		launchGame(Board *board, Player *pl1, Player *pl2)
{
  while (!board->isWinner())
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
  launchGame(new Board(19), new Human(), new IA());
}
