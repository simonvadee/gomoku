#include "Board.hh"

Board::Board(unsigned int size) : _board(new int[size * size])
{
  ;
}

Board::~Board()
{

}


int		Board::getAlignement(unsigned int pos, std::pair<unsigned int, unsigned int> dir, PLAYER player)
{

}

bool		Board::doubleThreeRule(unsigned int pos, PLAYER player)
{

}

int		Board::move(unsigned int pos, PLAYER player)
{
  this->_board[pos] = static_cast<int>(player);
}
