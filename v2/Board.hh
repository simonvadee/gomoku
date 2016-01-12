#ifndef BOARD_H_
# define BOARD_H_

# include <iostream>
# include <utility>
# include "Player.hh"

class Board
{
public:
  Board(unsigned int size);
  ~Board();


  int		getAlignement(unsigned int pos, std::pair<unsigned int, unsigned int> dir, PLAYER player);
  int		move(unsigned int pos, PLAYER player);
  bool		doubleThreeRule(unsigned int pos, PLAYER player);


  private:

  int		*_board;
};

#endif /* !BOARD_H_ */
