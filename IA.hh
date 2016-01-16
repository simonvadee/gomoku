#ifndef IA_H_
# define IA_H_

# include <ctime>
# include "Player.hh"

#define MAXINT 2147483647

class IA : public Player
{
public:
  IA(Board *board, Gui *gui, PLAYER player);
  ~IA();

public:
  int		findPossibleMoves(Pos* possibleMoves);
  int		negamax(Pos pos, int depth, int alpha, int beta, bool maximize);
  void		copyBoard();
  bool		play();
  void		repr();
  int		checkDirection(Pos& pos, Pos& dir);
  int		isFriendAligned(Pos& pos, Pos& dir);

  int		megaval(Pos& pos, PLAYER player);

private:
  int		_recursionNumber;
  int		_size;
  char**	_map;
};

#endif /* !IA_H_ */
