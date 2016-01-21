#ifndef MINMAX_HH_
# define MINMAX_HH_

# include "SafeQueue.hh"
# include "Board.hh"
# include "Eval.hh"

# define MAXINT 2147483647

class				MinMax
{
public:
  MinMax(SafeQueue* toProcess, unsigned int mapSize, char** map);
  ~MinMax();

private:
  SafeQueue*			_stock;
  Eval*				_eval;
  std::vector<Pos>*		_toProcess;
  unsigned int			_size;
  PLAYER			_id;
  char**			_map;
  char**			_baseMap;

public:
  void				process();
  void				getBestMove();
  char**			copyBoard(char **copy);
  int				findPossibleMoves(Pos* pos, PLAYER);
  int				minmax(Pos pos, int depth, int alpha, int beta, bool);
  void				repr();
  int				checkDirection(Pos& pos, Pos& dir);
  int				isFriendAligned(Pos& pos, Pos& dir);
  int				megaval(Pos& pos, PLAYER player);

private:

};

#endif
