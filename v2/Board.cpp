#include "Board.hh"

Board::Board(Options *options) : _size(options->size)
{
  _board = new int*[options->size];
  for (int x = 0; x < options->size; ++x)
    {
      _board[x] = new int[options->size];
      for (int y = 0; y < options->size; ++y)
  	_board[x][y] = 0;
    }
  _dir[0] = {1, 0};
  _dir[1] = {0, 1};
  _dir[2] = {1, -1};
  _dir[3] = {1, 1};
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

int		Board::getAlignement(Pos pos, Pos dir, PLAYER player)
{
  int		ret = 0;
  Pos		origPos;

  origPos.x = pos.x;
  origPos.y = pos.y;
  while (pos.x >= 0 && pos.x < _size && pos.y >= 0 && pos.y < _size && _board[pos.x][pos.y] == player)
    {
      pos.x += dir.x;
      pos.y += dir.y;
      ret += 1;
    }
  pos.x = origPos.x;
  pos.y = origPos.y;
  while (pos.x >= 0 && pos.x < _size && pos.y >= 0 && pos.y < _size && _board[pos.x][pos.y] == player)
    {
      pos.x -= dir.x;
      pos.y -= dir.y;
      ret += 1;
    }
  return ret - 1;
}

bool		Board::doubleThreeRule(Pos pos, PLAYER player)
{

}

void		Board::addScore(PLAYER player)
{
  _score[player - 1] += 2;
}

void		Board::delEatenPieces(Pos del1, Pos del2, Pos allied, PLAYER player)
{
  if (del1.x >= 0 && del2.x >= 0 && allied.x >= 0
      && del1.x < _size && del2.x < _size && allied.x < _size
      && del1.y >= 0 && del2.y >= 0 && allied.y >= 0
      && del1.y < _size && del2.y < _size && allied.y < _size
      && _board[del1.x][del1.y] == OPPONENT(player) && _board[del2.x][del2.y] == OPPONENT(player)
      && _board[allied.x][allied.y] == player)
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
      del1 = {pos.x + _dir[i].x, pos.y + _dir[i].y};
      del2 = {pos.x + (_dir[i].x * 2), pos.y + (_dir[i].y * 2)};
      allied = {pos.x + (_dir[i].x * 3), pos.y + (_dir[i].y * 3)};
      this->delEatenPieces(del1, del2, allied, player);
      del1 = {pos.x - _dir[i].x, pos.y - _dir[i].y};
      del2 = {pos.x - (_dir[i].x * 2), pos.y - (_dir[i].y * 2)};
      allied = {pos.x - (_dir[i].x * 3), pos.y - (_dir[i].y * 3)};
      this->delEatenPieces(del1, del2, allied, player);
    }
}

bool		Board::move(Pos pos, PLAYER player)
{
  if (doubleThreeRule(pos, player))
    return -1;
  this->eats(pos, player);
  this->_board[pos.x][pos.y] = static_cast<int>(player);
  return true;
}

bool		Board::isWinner()
{
  return (this->_score[PLAYER1 - 1] >= 10
	  || this->_score[PLAYER2 - 1] >= 10
	  || this->getAlignement(_lastMove, _dir[HORIZONTAL], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[VERTICAL], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[DIAGONAL_LR], _lastPlayer) == 5
	  || this->getAlignement(_lastMove, _dir[DIAGONAL_RL], _lastPlayer) == 5);
}
