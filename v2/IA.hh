#ifndef IA_H_
# define IA_H_

# include "Player.hh"

#define MAXINT 2147483647

class IA : public Player
{
public:
  IA(Board *board, Gui *gui, PLAYER player);
  ~IA();

  int		findPossibleMoves(Pos pos, Pos* possibleMoves);
  int		negamax(Pos pos, int depth, int alpha, int beta);
  bool		play();
  int		megaval(Pos& pos);

private:
  int		_recursionNumber;

};

#endif /* !IA_H_ */
