#include "Board.hh"

Rules*	Rules::_rules = NULL;

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

Rules::Rules(int rules)
  : _rulesMask(rules)
{}

Rules::~Rules()
{}

void	Rules::setRules(int rules)
{
  _rules->_rulesMask = rules;
}

int	Rules::getRules()
{
  return (_rules->_rulesMask);
}

void	Rules::setSize(unsigned int size)
{
  _rules->_size = size;
}

unsigned int	Rules::getSize()
{
  return (_rules->_size);
}

unsigned int	Rules::getNegaDepth()
{
  return (_rules->_negaDepth);
}

unsigned int	Rules::getCheckZone()
{
  return (_rules->_checkZone);
}

void		Rules::setTime(TIME time)
{
  if (time == TIME::T10)
    {
      _rules->_negaDepth = 1;
      _rules->_checkZone = 2;
    }
  if (time == TIME::T20)
    {
      _rules->_negaDepth = 2;
      _rules->_checkZone = 1;
    }
  if (time == TIME::T50)
    {
      _rules->_negaDepth = 2;
      _rules->_checkZone = 2;
    }
}

void	Rules::instanciateRules()
{
  if (_rules == NULL)
    _rules = new Rules(0xfff0);
}

void	Rules::destroyRules()
{
  if (_rules != NULL)
    {
      delete (_rules);
      _rules = NULL;
    }
}

Board::Board()
{
  _board = new char*[Rules::getSize()];
  for (int x = 0; x < Rules::getSize(); ++x)
    {
      _board[x] = new char[Rules::getSize()];
      for (int y = 0; y < Rules::getSize(); ++y)
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
  return (pos.x >= 0 && pos.x < Rules::getSize() && pos.y >= 0 && pos.y < Rules::getSize());
}

int		Board::operator[](Pos pos)
{
  if (pos.x < 0 || pos.x >= Rules::getSize() || pos.y < 0 || pos.y >= Rules::getSize())
    return -1;

  return _board[pos.x][pos.y];
}

bool		Board::isCaseBreakable(char** map, Pos pos, PLAYER player)
{
  Pos		inversDir;

  for (unsigned int i = 0; i < 4; ++i)
    {
      inversDir.x = -_dir[i].x;
      inversDir.y = -_dir[i].y;
      if (alignBreak(map, pos, _dir[i], player)
	  || alignBreak(map, pos, inversDir, player))
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
      if (checkBreakable && isCaseBreakable(map, pos, player))
	return ret;
      pos += dir;
      ret += 1;
    }
  pos = origPos - dir;
  while (validPos(pos)
	 && map[pos.x][pos.y] == player)
    {
      if (checkBreakable && isCaseBreakable(map, pos, player))
	return ret;
      pos -= dir;
      ret += 1;
    }
  return ret;
}

bool		Board::checkNeighbours(char **map, std::string line, int index, PLAYER player, Pos key, Pos size)
{
  int		pos = 0;
  Pos		newPos;
  int		x;

  if (doubleThreeRule(map, key, player, index) == false)
    return false;

  if (index == 0)
    {
      for (x = key.x - size.x; x < key.x + size.y; x++)
	{
	  if ((line[pos] - 48) == player)
	    {
	      newPos.x = x;
	      newPos.y = key.y;
	      if (x != key.x && doubleThreeRule(map, newPos, player, index) == false)
		return false;
	    }
	  ++pos;
	}
    }
  if (index == 1)
    {
      for (x = key.y - size.x; x < key.y + size.y; x++)
	{
	  if ((line[pos] - 48) == player)
	    {
	      newPos.x = key.x;
	      newPos.y = x;
	      if (x != key.y && doubleThreeRule(map, newPos, player, index) == false)
		return false;
	    }
	  ++pos;
	}
    }
  if (index == 2)
    {
      for (x = key.x - size.x; x < key.x + size.y; x++)
	{
	  if ((line[pos] - 48) == player)
	    {
	      newPos.x = x;
	      newPos.y = key.x + key.y - x;
	      if (x != key.x && doubleThreeRule(map, newPos, player, index) == false)
		return false;
	    }
	  ++pos;
	}
    }
  if (index == 3)
    {
      for (x = key.x - size.x; x < key.x + size.y; x++)
	{
	  newPos.y = key.y - key.x + x;
	  newPos.x = x;
	  if ((line[pos] - 48) == player)
	    {
	      if (x != key.y && doubleThreeRule(map, newPos, player, index) == false)
		return false;
	    }
	  ++pos;
	}
    }
  return true;
}

bool				Board::checkDoubleThree(char **map, PLAYER player, Pos key, int lineChecked, std::string data[4])
{
  static const std::string	pool[6] = {"01110", "010110", "011010","02220", "020220", "022020"};
  Pos				pos;

  for (int index = 0; index < 4; index++)
    {
      for (int id = 0; id < 6; id++)
	{
	  pos.x = data[index].find(pool[id]);
	  if (pos.x != -1)
	    {
	      if (lineChecked != -1)
		  return false;
	      else
		{
		  pos.x = 4 - pos.x;
		  pos.y = -2 - pos.x + pool[id].size();
		  if (checkNeighbours(map, pool[id], index, player, key, pos) == false)
		    return false;
		}
	    }
	}
    }
  return true;
}

bool		Board::doubleThreeRule(char **map, Pos pos, PLAYER player, int lineChecked)
{
  std::string			data[4];
  int old;

  if (lineChecked == -1)
    {
      old = map[pos.x][pos.y];
      map[pos.x][pos.y] = player;
    }

  for (int x = pos.x - 4; x < pos.x + 5; x++)
    {
      for (int y = pos.y - 4; y < pos.y + 5; y++)
	{
	  if (y == pos.y && lineChecked != 0)
	    if (x < 0 || x >= Rules::getSize())
	      data[0].push_back('3');
	    else
	      data[0].push_back(map[x][y] + 48);
	  if (x == pos.x && lineChecked != 1)
	    if (y < 0 || y >= Rules::getSize())
	      data[1].push_back('3');
	    else
	      data[1].push_back(map[x][y] + 48);
	  if ((pos.x - x) + (pos.y - y) == 0 && lineChecked != 2)
	    if (y < 0 || x < 0 || x >= Rules::getSize() || y >= Rules::getSize())
	      data[2].push_back('3');
	    else
	      data[2].push_back(map[x][y] + 48);
	  if (pos.x - x == pos.y - y  && lineChecked != 3)
	    if (y < 0 || x < 0 || x >= Rules::getSize() || y >= Rules::getSize())
	      data[3].push_back('3');
	    else
	      data[3].push_back(map[x][y] + 48);
	}
    }
  bool ret = checkDoubleThree(map, player, pos, lineChecked, data);
  if (lineChecked == -1)
    map[pos.x][pos.y] = old;
  return ret;
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

bool		Board::canEatPieces(char **map, Pos del1, Pos del2, Pos allied, PLAYER player)
{
  if (map[del1.x][del1.y] == OPPONENT(player) && map[del2.x][del2.y] == OPPONENT(player)
      && map[allied.x][allied.y] == player)
    return true;
  return false;
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
  return !(((Rules::getRules() & RULE_THREE) && doubleThreeRule(map, pos, player, -1) == false)
	   || map[pos.x][pos.y] != 0);
}

bool		Board::isCaseInteresting(char** map, int checkSize, Pos pos, PLAYER player)
{
  for (int x = pos.x - checkSize; x != pos.x + checkSize + 1; ++x)
    {
      for (int y = pos.y - checkSize; y != pos.y + checkSize + 1; ++y)
	{
	  if (x >= 0 && x < Rules::getSize()
	      && y >= 0 && y < Rules::getSize()
	      && !(x == pos.x && y == pos.y)
	      && map[x][y] != 0)
	    return true;
	}
    }
  return false;
}

bool		Board::move(Pos pos, PLAYER player)
{
  if ((Rules::getRules() & RULE_THREE) && doubleThreeRule(_board, pos, player, -1) == false
      || (*this)[pos] != 0)
    return false;
  if (Rules::getRules() & RULE_EAT)
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
	  || this->getAlignement(_board, _lastMove, _dir[HORIZONTAL], _lastPlayer, Rules::getRules() & RULE_BREAK) == 5
	  || this->getAlignement(_board, _lastMove, _dir[VERTICAL], _lastPlayer, Rules::getRules() & RULE_BREAK) == 5
	  || this->getAlignement(_board, _lastMove, _dir[DIAGONAL_LR], _lastPlayer, Rules::getRules() & RULE_BREAK) == 5
	  || this->getAlignement(_board, _lastMove, _dir[DIAGONAL_RL], _lastPlayer, Rules::getRules() & RULE_BREAK) == 5);
}

void		Board::cleanMap()
{
  for (int x = 0; x < Rules::getSize(); ++x)
    {
      for (int y = 0; y < Rules::getSize(); ++y)
  	_board[x][y] = 0;
    }
}
