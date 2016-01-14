#include "IA.hh"

extern Pos _dir[4];

IA::IA(Board *board, Gui *gui, PLAYER player) : Player(board, gui, player),
						_recursionNumber(10),
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

int		IA::isFriendAligned(Pos& pos, Pos& dir)
{
  return (0);
}

int		IA::findPossibleMoves(Pos pos, Pos* possibleMoves)
{
  // push all possible moves in possibleMoves
  return 0;
}

int		IA::checkDirection(Pos& pos, Pos& dir)
{
  return (isFriendAligned(pos, dir));
}

int		IA::megaval(Pos& pos)
{
  Pos		inversDir;
  int		weight = 0;

  for (unsigned int i = 0; i < 4; ++i)
    {
      inversDir.x = -_dir[i].x;
      inversDir.y = -_dir[i].y;
      weight += checkDirection(pos, _dir[i]) + checkDirection(pos, inversDir);
    }
  return weight;
}

int		IA::negamax(Pos pos, int depth, int alpha, int beta)
{
  int		best, value;
  Pos		*possibleMoves;

  if (depth == _recursionNumber)
    return megaval(pos);

  _map[pos.x][pos.y] = depth % 2 + _id;
  best = -MAXINT;
  for (unsigned int i = 0; i < findPossibleMoves(pos, possibleMoves); ++i)
    {
      value = -negamax(possibleMoves[i], depth + 1, -beta, -alpha);
      _map[pos.x][pos.y] = 0;
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
  int		best, value = 0;
  Pos		*possibleMoves;

  copyBoard();
  for (unsigned int i = 0; i < findPossibleMoves(pos, possibleMoves); ++i)
    {
      value = negamax(possibleMoves[i], 0, -MAXINT, MAXINT);
      if (value > best)
	{
	  best = value;
	  pos = possibleMoves[i];
	}
    }
  _board->move(pos, _id);
  _gui->updateDisplay();
}
