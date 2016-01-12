# include "Board.hh"
# include "IA.hh"
# include "Human.hh"

void		launchGame(Board *board, Player *pl1, Player *pl2)
{

}

int		main()
{
  launchGame(new Board(19), new Human(), new IA());
}
