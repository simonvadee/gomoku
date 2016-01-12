#ifndef BOARD_H_
# define BOARD_H_

# include <iostream>
# include <utility>
# include <vector>

typedef enum
  {
    PLAYER1 = 0,
    PLAYER2
  } PLAYER;

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

  int		getAlignement(int *pos, std::pair<int, int> dir, PLAYER player);
  bool		move(int pos[2], PLAYER player);
  void		eats(int pos[2], PLAYER player);
  bool		doubleThreeRule(int pos[2], PLAYER player);
  bool		isWinner();
  int**		getBoard() const;

  private:

  unsigned int			_size;
  int				**_board;
  int				_lastMove[2];
  PLAYER			_lastPlayer;
  std::vector<std::pair<int, int> >	_dir;
  int				_score[2];
};

#endif /* !BOARD_H_ */
