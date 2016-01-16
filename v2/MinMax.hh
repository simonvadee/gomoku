#ifndef MINMAX_HH_
# define MINMAX_HH_

# include "SafeQueue.hh"
# include "Board.hh"

# define MAXINT 2147483647

class				MinMax
{
public:
  MinMax(SafeQueue* toProcess);
  ~MinMax();

private:
  Board*			_board;

  SafeQueue*			_stock;
  std::pair<char**, Pos>*	_toProcess;
  int				_recursionNumber;
  int				_size;
  PLAYER			_id;
  char**			_map;

public:
  void				process();
  int				findPossibleMoves(Pos pos, Pos* possibleMoves);
  int				negamax(Pos pos, int depth, int alpha, int beta);
  void				repr();
  int				checkDirection(Pos& pos, Pos& dir);
  int				isFriendAligned(Pos& pos, Pos& dir);
  int				megaval(Pos& pos, PLAYER player);

private:
  
};

#endif
