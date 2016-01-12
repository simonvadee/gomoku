#ifndef BOARD_H_
# define BOARD_H_

# include <iostream>
# include <utility>
# include <vector>
# include "Player.hh"

typedef enum
  {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_LR,
    DIAGONAL_RL
  }	DIRECTION;

class Board
{
public:
  Board(unsigned int size);
  ~Board();


  int		getAlignement(unsigned int pos, std::pair<unsigned int, unsigned int> dir, PLAYER player);
  int		move(unsigned int pos, PLAYER player);
  bool		doubleThreeRule(unsigned int pos, PLAYER player);
  bool		isWinner();
  std::vector<int>*	getBoard() const;

  private:

  std::vector<int>		*_board;
  unsigned int  _lastMove;
  PLAYER	_lastPlayer;
  std::vector<std::pair<int, int> > _dir;
};

#endif /* !BOARD_H_ */