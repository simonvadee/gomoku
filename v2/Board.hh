#ifndef BOARD_H_
# define BOARD_H_


class Board
{
  public:
  Board(unsigned int size);
  ~Board();


  int		getAlignement(unsigned int pos, std::pair dir);
  int		move(pos);
  bool		doubleThreeRule(int pos);


  private:

  int		*_board;
};

#endif /* !BOARD_H_ */
