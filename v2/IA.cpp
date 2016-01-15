#include "IA.hh"

extern Pos _dir[4];

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player),
						_recursionNumber(2),
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

int		IA::findPossibleMoves(Pos pos, Pos* possibleMoves)
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
  static int res = 0;
  Pos		inversDir;
  int		weight = 0;

  return res++;
  // for (unsigned int i = 0; i < 4; ++i)
  //   {
  //     inversDir.x = -_dir[i].x;
  //     inversDir.y = -_dir[i].y;
  //     weight += checkDirection(pos, _dir[i]) + checkDirection(pos, inversDir);
  //   }
  // return weight;
}

int		IA::negamax(Pos pos, int depth, int alpha, int beta)
{
  int		best, value, nbPossibleMoves;
  Pos		possibleMoves[361];

  if (depth == _recursionNumber) {
    // std::cout << "depth = " << depth << " -> ";
    // repr();
    return megaval(pos, static_cast<PLAYER>((depth + _id) % 2 + 1));
  }
  _map[pos.x][pos.y] = (depth + _id) % 2 + 1;
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
  nbPossibleMoves = findPossibleMoves(pos, possibleMoves);
  best = -MAXINT;
  for (unsigned int i = 0; i < nbPossibleMoves; ++i)
    {
      value = negamax(possibleMoves[i], 0, -MAXINT, MAXINT);
      if (value > best)
      	{
      	  best = value;
      	  pos = possibleMoves[i];
      	}
    }
  std::clock_t	end = std::clock();
  std::cout << static_cast<int>(pos.x) << ":" << static_cast<int>(pos.y) << " player = " << _id << " in [" << 1000.0 * (end-start) / CLOCKS_PER_SEC << " ms]" << std::endl;
  _board->move(pos, _id);
  _gui->updateDisplay();
}
