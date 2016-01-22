#include <unistd.h>
#include <cmath>
#include "MinMax.hh"

extern Pos _dir[4];

MinMax::MinMax(SafeQueue* stock, unsigned int mapSize, char** map)
  : _stock(stock), _eval(new Eval("")), _size(mapSize), _baseMap(map)
{
  process();
}

MinMax::~MinMax()
{
  delete _eval;
}

void		MinMax::process()
{
  while (_stock->isGameRunning())
    {
      if ((_toProcess = _stock->popStock()) != NULL)
	{
	  getBestMove();
	  delete _toProcess;
	}
      else
	usleep(30);
    }
}

void		MinMax::getBestMove()
{
  Pos		best;
  Pos		tmp;
  int		res, max = -MAXINT;

  _id = _stock->getTurn();
  _map = copyBoard(_map);
  while (_toProcess->size() > 0)
    {
      tmp = _toProcess->back();
      _map[tmp.x][tmp.y] = _id;
      if ((res = minmax(tmp, 1, -MAXINT, MAXINT, false)) > max)
	{
	  best = tmp;
	  max = res;
	}
      _map[tmp.x][tmp.y] = 0;
      _toProcess->pop_back();
    }
  _stock->fillProcessed(new std::pair<int, Pos>(max, best));
}

char**		MinMax::copyBoard(char **copy)
{
  copy = new char*[_size];
  for (unsigned int x = 0; x < _size; ++x)
    {
      copy[x] = new char[_size];
      for (unsigned int y = 0; y < _size; ++y)
	copy[x][y] = _baseMap[x][y];
    }
  return copy;
}

void		MinMax::repr()
{
  for (unsigned int x = 0; x < _size; ++x)
    for (unsigned int y = 0; y < _size; ++y)
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

  for (unsigned int x = 0; x < _size; ++x)
    for (unsigned int y = 0; y < _size; ++y)
      {
	Pos pos;
	pos.x = x;
	pos.y = y;
	if (Board::isCaseInteresting(_map, Rules::getCheckZone(), pos, player)
	    && Board::isCasePlayable(_map, pos, player))
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

int		MinMax::minmax(Pos pos, int depth, int alpha, int beta, bool maximize)
{
  int		best, value, nbPossibleMoves;
  Pos		possibleMoves[361];
  Pos		move;
  PLAYER	player = static_cast<PLAYER>(depth % 2 == 0 ? _id : OPPONENT(_id));

  if (depth == Rules::getNegaDepth())
    return _eval->megaval(_map, pos, _id);

  nbPossibleMoves = findPossibleMoves(possibleMoves, player);
  if (maximize)
    {
      best = -MAXINT;
      for (unsigned int i = 0; i < nbPossibleMoves; ++i)
	{
	  _map[possibleMoves[i].x][possibleMoves[i].y] = player;
	  value = minmax(possibleMoves[i], depth + 1, alpha, beta, false);
	  _map[possibleMoves[i].x][possibleMoves[i].y] = 0;
	  if (value > best)
	    {
	      best = value;
	      move = possibleMoves[i];
	    }
	  alpha = MAX(alpha, best);
	  if (beta <= alpha)
	    break;
	}
    }
  else
    {
      best = MAXINT;
      for (unsigned int i = 0; i < nbPossibleMoves; ++i)
	{
	  _map[possibleMoves[i].x][possibleMoves[i].y] = player;
	  value = minmax(possibleMoves[i], depth + 1, alpha, beta, true);
	  _map[possibleMoves[i].x][possibleMoves[i].y] = 0;
	  if (value < best)
	    {
	      best = value;
	      move = possibleMoves[i];
	    }
	  beta = MIN(beta, best);
	  if (beta <= alpha)
	    break;
	}
    }
  return best + _eval->megaval(_map, pos, _id);
}
