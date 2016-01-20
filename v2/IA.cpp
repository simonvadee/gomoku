#include "IA.hh"
#include "GameCore.hh"

extern Pos _dir[4];

IA::IA(Board *board, Gui *gui, PLAYER player, SafeQueue* shared)
  : Player(board, gui, player),
    _size(board->getSize()),
    _shared(shared),
    _toTreat(new std::vector<Pos>())
{
  _map = _board->getBoard();
}

IA::~IA()
{
}

int		IA::findPossibleMoves()
{
  Pos		pos;

  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      {
	pos.x = x;
	pos.y = y;
	if (_board->isCasePlayable(_map, pos, _id))
	  {
	    _toTreat->push_back(pos);
	  }
      }
  return _toTreat->size();
}

void		IA::dispatcher()
{
  float		coeff = (float)_toTreat->size() / (float)MAX_THREAD;

  _shared->setTurn(_id);
  for (int i = 0; i < MAX_THREAD; ++i)
    _shared->fillStock(new std::vector<Pos>(_toTreat->begin() + i * coeff, _toTreat->begin() + (i + 1) * coeff));
}

char**		IA::copyBoard(char **copy, Pos pos)
{
  char		**ptr = _board->getBoard();

  copy = new char*[_size];
  for (int x = 0; x < _size; ++x)
    {
      copy[x] = new char[_size];
      for (int y = 0; y < _size; ++y)
  	copy[x][y] = 0;
    }
  for (int x = 0; x < _size; ++x)
    for (int y = 0; y < _size; ++y)
      copy[x][y] = ptr[x][y];
  copy[pos.x][pos.y] = _id;
  return copy;
}

bool			IA::play()
{
  int			i = 0;
  int			best, value = 0;
  Pos			pos;
  std::clock_t		start = std::clock();
  std::pair<int, Pos>*	res;

  _toTreat->clear();
  findPossibleMoves();
  dispatcher();
  best = -MAXINT;
  while (i < MAX_THREAD)
    {
      if ((res = _shared->popProcessed()) != NULL)
  	{
	  ++i;
  	  if (res->first > best)
  	    {
  	      best = res->first;
  	      pos = res->second;
  	    }
	  // delete res;
  	}
    }
  std::clock_t	end = std::clock();
  std::cout << static_cast<int>(pos.x) << ":" << static_cast<int>(pos.y) << " player = " << _id << " in [" << 1000.0 * (end-start) / CLOCKS_PER_SEC << " ms] weight = " << best << std::endl;
  _board->move(pos, _id);
  _gui->updateDisplay();
}
