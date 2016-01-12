#include "Board.hh"

Board::Board(unsigned int size) : _board(new std::vector<int>(size * size, 0))
{
  _dir.push_back(std::pair<unsigned int, unsigned int>(1, 0));
  _dir.push_back(std::pair<unsigned int, unsigned int>(0, 1));
  _dir.push_back(std::pair<unsigned int, unsigned int>(-1, 1));
  _dir.push_back(std::pair<unsigned int, unsigned int>(-1, -1));
}

Board::~Board()
{

}

std::vector<int>*		Board::getBoard() const
{
  return _board;
}

int		Board::getAlignement(unsigned int pos, std::pair<unsigned int, unsigned int> dir, PLAYER player)
{

}

bool		Board::doubleThreeRule(unsigned int pos, PLAYER player)
{

}

int		Board::move(unsigned int pos, PLAYER player)
{
  (*this->_board)[pos] = static_cast<int>(player);
}

bool		Board::isWinner()
{
  return (this->getAlignement(_lastMove, _dir[HORIZONTAL], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[VERTICAL], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[DIAGONAL_LR], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[DIAGONAL_RL], _lastPlayer) == 5);
}
