#ifndef IA_HH_
# define IA_HH_

# include <ctime>
# include "Player.hh"
# include "SafeQueue.hh"
# include "MinMax.hh"

class IA : public Player
{
public:
  IA(Board *board, Gui *gui, PLAYER player, SafeQueue* shared);
  ~IA();

public:
  char**	copyBoard(char** copy, Pos);
  bool		play();
  int		findPossibleMoves(Pos pos, Pos* possibleMoves);

private:
  SafeQueue*	_shared;
  int		_recursionNumber;
  int		_size;
  char**	_map;
};

#endif /* !IA_H_ */
