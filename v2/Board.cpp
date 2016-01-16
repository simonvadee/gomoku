#include "Board.hh"

Pos _dir[4] =
  {
    {1, 0},
    {0, 1},
    {1, -1},
    {1, 1}
  };

Pos&	operator+=(Pos& pos1, Pos& pos2)
{
  pos1.x += pos2.x;
  pos1.y += pos2.y;
  return pos1;
}

Pos	operator-(Pos pos1, Pos pos2)
{
  Pos	ret;

  ret.x = pos1.x - pos2.x;
  ret.y = pos1.y - pos2.y;
  return ret;
}

Pos&	operator-=(Pos& pos1, Pos& pos2)
{
  pos1.x -= pos2.x;
  pos1.y -= pos2.y;
  return pos1;
}

Pos	operator+(Pos pos1, Pos pos2)
{
  Pos	ret;

  ret.x = pos1.x + pos2.x;
  ret.y = pos1.y + pos2.y;
  return ret;
}

Pos	operator*(Pos pos1, int mul)
{
  Pos	ret;

  ret.x = pos1.x * mul;
  ret.y = pos1.y * mul;
  return ret;
}

Board::Board(int size)
  : _size(size),
    _rules(0xfff0)
{
  _board = new char*[_size];
  for (int x = 0; x < _size; ++x)
    {
      _board[x] = new char[_size];
      for (int y = 0; y < _size; ++y)
  	_board[x][y] = 0;
    }
  _score[PLAYER1 - 1] = 0;
  _score[PLAYER2 - 1] = 0;
}

Board::~Board()
{

}

char**		Board::getBoard()
{
  return _board;
}

bool		Board::alignBreak(char **map, Pos pos, Pos dir, PLAYER player)
{
  return ((validPos(pos - dir) && validPos(pos + dir) && validPos(pos + dir*2)
	   && (map[pos.x - dir.x][pos.y - dir.y] == OPPONENT(player))
	   && (map[pos.x + dir.x][pos.y + dir.y] == player)
	   && (map[pos.x + (dir.x * 2)][pos.y + (dir.y * 2)] == 0))
	  ||
	  (validPos(pos - dir) && validPos(pos + dir) && validPos(pos + dir*2)
	   && (map[pos.x - dir.x][pos.y - dir.y] == 0)
	   && (map[pos.x + dir.x][pos.y + dir.y] == player)
	   && (map[pos.x + (dir.x * 2)][pos.y + (dir.y * 2)] == OPPONENT(player)))
	  ||
	  (validPos(pos + dir) && validPos(pos - dir) && validPos(pos - dir*2)
	   && (map[pos.x + dir.x][pos.y + dir.y] == 0)
	   && (map[pos.x - dir.x][pos.y - dir.y] == player)
	   && (map[pos.x - (dir.x * 2)][pos.y - (dir.y * 2)] == OPPONENT(player)))
	  ||
	  (validPos(pos + dir) && validPos(pos - dir) && validPos(pos - dir*2)
	   && (map[pos.x + dir.x][pos.y + dir.y] == OPPONENT(player))
	   && (map[pos.x - dir.x][pos.y - dir.y] == player)
	   && (map[pos.x - (dir.x * 2)][pos.y - (dir.y * 2)] == 0)));
}

bool		Board::validPos(Pos pos)
{
  return (pos.x >= 0 && pos.x < _size && pos.y >= 0 && pos.y < _size);
}

int		Board::operator[](Pos pos)
{
  if (pos.x < 0 || pos.x >= _size || pos.y < 0 || pos.y >= _size)
    return -1;

  return _board[pos.x][pos.y];
}

bool		Board::isCaseBreakable(Pos pos, PLAYER player)
{
  Pos		inversDir;

  for (unsigned int i = 0; i < 4; ++i)
    {
      inversDir.x = -_dir[i].x;
      inversDir.y = -_dir[i].y;
      if (this->alignBreak(_board, pos, _dir[i], player)
	  || this->alignBreak(_board, pos, inversDir, player))
	return true;
    }
  return false;
}

int		Board::getAlignement(char **map, Pos pos, Pos dir, PLAYER player, bool checkBreakable)
{
  int		ret = 1;
  Pos		origPos = pos;

  pos += dir;
  while (validPos(pos)
	 && map[pos.x][pos.y] == player)
    {
      if (checkBreakable && isCaseBreakable(pos, player))
	return ret;
      pos += dir;
      ret += 1;
    }
  pos = origPos - dir;
  while (validPos(pos)
	 && map[pos.x][pos.y] == player)
    {
      if (checkBreakable && isCaseBreakable(pos, player))
	return ret;
      pos -= dir;
      ret += 1;
    }
  return ret;
}

bool		Board::doubleThreeRule(Pos pos, PLAYER player)
{
  return false;
}

void		Board::addScore(PLAYER player)
{
  _score[player - 1] += 2;
}

void		Board::delEatenPieces(Pos del1, Pos del2, Pos allied, PLAYER player)
{
  if ((*this)[del1] == OPPONENT(player) && (*this)[del2] == OPPONENT(player)
      && (*this)[allied] == player)
    {
      _board[del1.x][del1.y] = 0;
      _board[del2.x][del2.y] = 0;
      this->addScore(player);
      std::cout << "remove" << std::endl;
    }
}

void		Board::eats(Pos pos, PLAYER player)
{
  Pos		del1;
  Pos		del2;
  Pos		allied;

  for (unsigned int i = 0; i < 4; ++i)
    {
      del1.x = pos.x + _dir[i].x;
      del1.y = pos.y + _dir[i].y;
      del2.x = pos.x + (_dir[i].x * 2);
      del2.y = pos.y + (_dir[i].y * 2);
      allied.x = pos.x + (_dir[i].x * 3);
      allied.y = pos.y + (_dir[i].y * 3);
      this->delEatenPieces(del1, del2, allied, player);
      del1.x = pos.x - _dir[i].x;
      del1.y = pos.y - _dir[i].y;
      del2.x = pos.x - (_dir[i].x * 2);
      del2.y = pos.y - (_dir[i].y * 2);
      allied.x = pos.x - (_dir[i].x * 3);
      allied.y = pos.y - (_dir[i].y * 3);
      this->delEatenPieces(del1, del2, allied, player);
    }
}

bool		Board::isCasePlayable(char** map, Pos pos, PLAYER player)
{
  return !(((_rules & RULE_THREE) && doubleThreeRule(pos, player))
	   || map[pos.x][pos.y] != 0);
}

bool		Board::move(Pos pos, PLAYER player)
{
  if ((_rules & RULE_THREE) && doubleThreeRule(pos, player)
      || (*this)[pos] != 0)
    return false;
  if (_rules & RULE_EAT)
    this->eats(pos, player);
  _lastPlayer = player;
  _lastMove = pos;
  _board[pos.x][pos.y] = static_cast<int>(player);
  return true;
}

bool		Board::isWinner()
{
  return (this->_score[PLAYER1 - 1] >= 10
	  || this->_score[PLAYER2 - 1] >= 10
	  || this->getAlignement(_board, _lastMove, _dir[HORIZONTAL], _lastPlayer, _rules & RULE_BREAK) == 5
	  || this->getAlignement(_board, _lastMove, _dir[VERTICAL], _lastPlayer, _rules & RULE_BREAK) == 5
	  || this->getAlignement(_board, _lastMove, _dir[DIAGONAL_LR], _lastPlayer, _rules & RULE_BREAK) == 5
	  || this->getAlignement(_board, _lastMove, _dir[DIAGONAL_RL], _lastPlayer, _rules & RULE_BREAK) == 5);
}

void		Board::setRules(int rules)
{
  _rules = rules;
}

void		Board::cleanMap()
{
  for (int x = 0; x < _size; ++x)
    {
      for (int y = 0; y < _size; ++y)
  	_board[x][y] = 0;
    }
}

unsigned int	Board::getSize() const
{
  return _size;
}
