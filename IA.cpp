#include "IA.hh"

extern Pos _dir[4];

# define MIN(a, b) a < b ? a : b
# define MAX(a, b) a > b ? a : b

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player),
						_recursionNumber(1),
						_size(board->getSize())
{
  _map = new char*[_size];
  for (int x = 0; x < _size; ++x)
    {
      _map[x] = new char[_size];
      for (int y = 0; y < _size; ++y)
  	_map[x][y] = 0;
    }
}

IA::~IA()
{
}

void		IA::repr()
{
  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      std::cout << static_cast<int>(_map[x][y]);
  std::cout << std::endl;
}

int		IA::isFriendAligned(Pos& pos, Pos& dir)
{
  return (0);
}

int		IA::findPossibleMoves(Pos* possibleMoves)
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

int		IA::checkDirection(Pos& pos, Pos& dir)
{
  return (isFriendAligned(pos, dir));
}

int		IA::megaval(Pos& pos, PLAYER player)
{
  Pos		inversDir;
  int		weight = 0;

  weight += _board->getAlignement(_map, pos, _dir[HORIZONTAL], player, false) - 1;
  weight += _board->getAlignement(_map, pos, _dir[VERTICAL], player, false) - 1;
  weight += _board->getAlignement(_map, pos, _dir[DIAGONAL_LR], player, false) - 1;
  weight += _board->getAlignement(_map, pos, _dir[DIAGONAL_RL], player, false) - 1;
  if (weight > 0)
    {
      std::cout << weight << " for " << (int)pos.x << ":" << (int)pos.y << "for player = " << player << std::endl;
    }
  return weight;
}

int		IA::negamax(Pos pos, int depth, int alpha, int beta, bool maximize)
{
  int		best, value, nbPossibleMoves;
  Pos		possibleMoves[361];
  PLAYER	player = static_cast<PLAYER>(depth % 2 == 0 ? OPPONENT(_id) : _id);

  if (depth == _recursionNumber)
    return megaval(pos, player);

  _map[pos.x][pos.y] = player;
  nbPossibleMoves = findPossibleMoves(possibleMoves);
  if (maximize)
    {
      best = -MAXINT;
      for (unsigned int i = 0; i < nbPossibleMoves; ++i)
	{
	  for (int j = 0; j < depth * 4; ++j)
	    std::cout << " ";
	  std::cout << "for pos = " << (int)possibleMoves[i].x << ":" << (int)possibleMoves[i].y << std::endl;
	  best = MAX(best, negamax(possibleMoves[i], depth + 1, alpha, beta, false));
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
	  for (int j = 0; j < depth * 4; ++j)
	    std::cout << " ";
	  best = MIN(best, negamax(possibleMoves[i], depth + 1, alpha, beta, true));
	  alpha = MIN(beta, best);
	  if (beta <= alpha)
	    break;
	}
    }
  _map[pos.x][pos.y] = 0;
  return best;
}

void		IA::copyBoard()
{
  char		**ptr = _board->getBoard();

  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      _map[x][y] = ptr[x][y];
}

bool		IA::play()
{
  Pos		pos;
  int		best, value, nbPossibleMoves = 0;
  Pos		possibleMoves[361];
  std::clock_t	start = std::clock();

  copyBoard();
  nbPossibleMoves = findPossibleMoves(possibleMoves);
  best = -MAXINT;
  for (unsigned int i = 0; i < nbPossibleMoves; ++i)
    {
      std::cout << "for pos = " << (int)possibleMoves[i].x << ":" << (int)possibleMoves[i].y << std::endl;
      value = negamax(possibleMoves[i], 0, -MAXINT, MAXINT, false);
      if (value > best)
      	{
      	  best = value;
      	  pos = possibleMoves[i];
	  std::cout << "best : " << value << std::endl;
      	}
    }
  std::clock_t	end = std::clock();
  std::cout << static_cast<int>(pos.x) << ":" << static_cast<int>(pos.y) << " player = " << _id << " in [" << 1000.0 * (end-start) / CLOCKS_PER_SEC << " ms] weight = " << best << std::endl;
  _board->move(pos, _id);
  _gui->updateDisplay();
}
