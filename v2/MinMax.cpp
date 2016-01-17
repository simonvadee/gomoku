#include <unistd.h>
#include "MinMax.hh"

extern Pos _dir[4];

# define MIN(a, b) a < b ? a : b
# define MAX(a, b) a > b ? a : b

MinMax::MinMax(SafeQueue* stock)
  : _stock(stock), _board(new Board(16)), _recursionNumber(2), _size(16)
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
	  _stock->fillProcessed(new std::pair<int, Pos>(negamax(_toProcess->second, 0, -MAXINT, MAXINT, true), _toProcess->second));
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

int		MinMax::findPossibleMoves(Pos* possibleMoves, PLAYER player)
{
  int		ret = 0;

  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      {
	Pos pos;
	pos.x = x;
	pos.y = y;
	if (_board->isCasePlayable(_map, pos, player))
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

  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      {
	Pos tmp;

	tmp.x = x;
	tmp.y = y;

	weight += _board->getAlignement(_map, tmp, _dir[HORIZONTAL], player, false) - 1;
	weight += _board->getAlignement(_map, tmp, _dir[VERTICAL], player, false) - 1;
	weight += _board->getAlignement(_map, tmp, _dir[DIAGONAL_LR], player, false) - 1;
	weight += _board->getAlignement(_map, tmp, _dir[DIAGONAL_RL], player, false) - 1;
      }
  return weight;
}

int		MinMax::negamax(Pos pos, int depth, int alpha, int beta, bool maximize)
{
  int		best, value, nbPossibleMoves;
  Pos		possibleMoves[361];
  Pos		move;
  PLAYER	player = static_cast<PLAYER>(depth % 2 == 0 ? _id : OPPONENT(_id));

  if (depth == _recursionNumber)
    return megaval(pos, _id);

  nbPossibleMoves = findPossibleMoves(possibleMoves, player);
  if (maximize)
    {
      best = -MAXINT;
      // std::cout << "depth = " << depth << " player = " << player << " values = ";
      for (unsigned int i = 0; i < nbPossibleMoves; ++i)
	{
	  _map[possibleMoves[i].x][possibleMoves[i].y] = player;
	  value = negamax(possibleMoves[i], depth + 1, alpha, beta, false);
	  _map[possibleMoves[i].x][possibleMoves[i].y] = 0;
	  if (value > best)
	    {
	      // std::cout << value << ", ";
	      best = value;
	      move = possibleMoves[i];

	    }
	  alpha = MAX(alpha, best);
	  if (beta <= alpha)
	    break;
	}
      // std::cout << std::endl;
    }
  else
    {
      best = MAXINT;
      // std::cout << "depth = " << depth << " player = " << player << " values = ";
      for (unsigned int i = 0; i < nbPossibleMoves; ++i)
	{
	  _map[possibleMoves[i].x][possibleMoves[i].y] = player;
	  value = negamax(possibleMoves[i], depth + 1, alpha, beta, true);
	  _map[possibleMoves[i].x][possibleMoves[i].y] = 0;
	  if (value < best)
	    {
	      // std::cout << value << ", ";
	      best = value;
	      move = possibleMoves[i];
	    }
	  beta = MIN(beta, best);
	  if (beta <= alpha)
	    break;
	}
      // std::cout << std::endl;
    }
  // if (depth < 2)
  //   std::cout << "BEST MOVE FOR DEPTH[PLAYER] = " << depth << '[' << player << "] value = " << best << "move : " << (int)move.x << ':' << (int)move.y << std::endl;
  return best;
}
