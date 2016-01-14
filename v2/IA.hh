#ifndef IA_H_
# define IA_H_

# include "Player.hh"

#define MAXINT 2147483647
#define MININT -2147483648

class IA : public Player
{
public:
  IA(Board *board, Gui *gui, PLAYER player);
  ~IA();

  Pos		negamax(Pos pos, int depth, int alpha, int beta);
  bool		play();

private:
  int		_recursionNumber;

};

#endif /* !IA_H_ */
