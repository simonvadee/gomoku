#include "Board.hh"

Board::Board(unsigned int size) : _size(size)
{
  _board = new int*[size];
  for (int x = 0; x < size; ++x)
    {
      _board[x] = new int[size];
      for (int y = 0; y < size; ++y)
	_board[x][y] = 0;
    }
  _board[0][0] = PLAYER1;
  _board[0][1] = PLAYER1;
  _board[0][2] = PLAYER1;
  _dir.push_back(std::pair<int, int>(1, 0));
  _dir.push_back(std::pair<int, int>(0, 1));
  _dir.push_back(std::pair<int, int>(1, -1));
  _dir.push_back(std::pair<int, int>(1, 1));
  _score[PLAYER1] = 0;
  _score[PLAYER2] = 0;
}

Board::~Board()
{

}

int**		Board::getBoard() const
{
  return _board;
}

int		Board::getAlignement(int pos[2], std::pair<int, int> dir, PLAYER player)
{
  int		ret = 0;
  int		origPos[2];

  origPos[0] = pos[0];
  origPos[1] = pos[1];
  while (pos[0] >= 0 && pos[0] < _size && pos[1] >= 0 && pos[1] < _size && _board[pos[0]][pos[1]] == player)
    {
      pos[0] += dir.first;
      pos[1] += dir.second;
      ret += 1;
    }
  pos[0] = origPos[0];
  pos[1] = origPos[1];
  while (pos[0] >= 0 && pos[0] < _size && pos[1] >= 0 && pos[1] < _size && _board[pos[0]][pos[1]] == player)
    {
      pos[0] -= dir.first;
      pos[1] -= dir.second;
      ret += 1;
    }
  return ret - 1;
}

bool		Board::doubleThreeRule(int pos[2], PLAYER player)
{

}

void		Board::eats(int pos[2], PLAYER player)
{

}

bool		Board::move(int pos[2], PLAYER player)
{
  if (doubleThreeRule(pos, player))
    return -1;
  this->eats(pos, player);
  this->_board[pos[0]][pos[1]] = static_cast<int>(player);
  return true;
}

bool		Board::isWinner()
{
  return (this->_score[PLAYER1] >= 10
	  || this->_score[PLAYER2] >= 10
	  || this->getAlignement(_lastMove, _dir[HORIZONTAL], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[VERTICAL], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[DIAGONAL_LR], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[DIAGONAL_RL], _lastPlayer) == 5);
}
