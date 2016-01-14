#ifndef IA_H_
# define IA_H_

# include "Player.hh"

#define MAXINT 2147483647

class IA : public Player
{
public:
  IA(Board *board, Gui *gui, PLAYER player);
  ~IA();

private:
  int		_recursionNumber;

public:
  int		findPossibleMoves(Pos pos, Pos* possibleMoves);
  int		negamax(Pos pos, int depth, int alpha, int beta);
  bool		play();
  int		megaval(Pos& pos);
  int		checkDirection(Pos& pos, Pos& dir);
  int		isFriendAligned(Pos& pos, Pos& dir);

private:
  bool		inMap(Pos& );
};

#endif /* !IA_H_ */
