#include <unistd.h>
#include "MinMax.hh"

extern Pos _dir[4];

MinMax::MinMax(SafeQueue* stock)
  : _stock(stock), _board(new Board(16)), _recursionNumber(1), _size(16)
{
  std::cout << "start thread" << std::endl;
  process();
}

MinMax::~MinMax()
{ 
}

void		MinMax::process()
{
  while (_stock->isGameRunning())
    {
      if ((_toProcess = _stock->popStock()) != NULL)
	{
	  if ((_map = _toProcess->first) == NULL)
	    continue;
	  _id = static_cast<PLAYER>(_map[_toProcess->second.x][_toProcess->second.y]);
	  _map[_toProcess->second.x][_toProcess->second.y] = 0;
	  _stock->fillProcessed(new std::pair<int, Pos>(negamax(_toProcess->second, 0, -MAXINT, MAXINT), _toProcess->second));
	  // free(_map);
	  // free(_toProcess);
	}
      else
	usleep(1);
    }
  std::cout << "end thread" << std::endl;
}

void		MinMax::repr()
{
  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      std::cout << static_cast<int>(_map[x][y]);
  std::cout << std::endl;
}

int		MinMax::isFriendAligned(Pos& pos, Pos& dir)
{
  return (0);
}

int		MinMax::findPossibleMoves(Pos pos, Pos* possibleMoves)
{
  int		ret = 0;

  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      {
	Pos pos;
	pos.x = x;
	pos.y = y;
	if (_board->isCasePlayable(_map, pos, _id))
	  {
	    possibleMoves[ret] = pos;
	    ret += 1;
	}
      }
  return ret;
}

int		MinMax::checkDirection(Pos& pos, Pos& dir)
{
  return (isFriendAligned(pos, dir));
}

int		MinMax::megaval(Pos& pos, PLAYER player)
{
  Pos		inversDir;
  int		weight = 0;

  weight += _board->getAlignement(_map, pos, _dir[HORIZONTAL], player, false) - 1;
  weight += _board->getAlignement(_map, pos, _dir[VERTICAL], player, false) - 1;
  weight += _board->getAlignement(_map, pos, _dir[DIAGONAL_LR], player, false) - 1;
  weight += _board->getAlignement(_map, pos, _dir[DIAGONAL_RL], player, false) - 1;
  return weight;
}

int		MinMax::negamax(Pos pos, int depth, int alpha, int beta)
{
  int		best, value, nbPossibleMoves;
  Pos		possibleMoves[361];
  PLAYER	player = static_cast<PLAYER>(depth % 2 == 0 ? _id : OPPONENT(_id));

  if (depth == _recursionNumber)
    return megaval(pos, player);

  _map[pos.x][pos.y] = player;
  best = -MAXINT;
  nbPossibleMoves = findPossibleMoves(pos, possibleMoves);
  for (unsigned int i = 0; i < nbPossibleMoves; ++i)
    {
      value = -negamax(possibleMoves[i], depth + 1, -beta, -alpha);
      if (value > best)
	{
	  best = value;
	  if (best > alpha)
	    {
	      alpha = best;
	      if (alpha > beta)
		{
		  _map[pos.x][pos.y] = 0;
		  return best;
		}
	    }
	}
    }
  _map[pos.x][pos.y] = 0;
  return best;
}
