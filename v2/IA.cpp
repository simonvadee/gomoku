#include "IA.hh"

extern Pos _dir[4];

# define MIN(a, b) a < b ? a : b
# define MAX(a, b) a > b ? a : b

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player),
						_recursionNumber(0),
						_size(Rules::getSize())
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

int		IA::findPossibleMoves(Pos* possibleMoves, PLAYER player)
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

int		IA::checkDirection(Pos& pos, Pos& dir)
{
  return (isFriendAligned(pos, dir));
}

int		IA::megaval(Pos& pos, PLAYER player)
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

int		IA::negamax(Pos pos, int depth, int alpha, int beta, bool maximize)
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
  if (depth == 0)
    _board->move(move, _id);
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
  std::clock_t	start = std::clock();

  copyBoard();
  pos.x = -1;
  negamax(pos, 0, -MAXINT, MAXINT, true);
  std::clock_t	end = std::clock();
  std::cout << "in [" << 1000.0 * (end-start) / CLOCKS_PER_SEC << " ms]" <<  std::endl;
  _gui->updateDisplay();
}
