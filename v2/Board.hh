#ifndef BOARD_H_
# define BOARD_H_

# include <iostream>
# include <utility>
# include <vector>

#define OPPONENT(x) (3 - x)

typedef enum
  {
    PLAYER1 = 1,
    PLAYER2
  } PLAYER;

typedef enum
  {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_LR,
    DIAGONAL_RL
  }	DIRECTION;

typedef struct
{
  unsigned int	size;
  int		rules;
}		Options;

typedef struct
{
  int		x;
  int		y;
}		Pos;

class Board
{
public:
  Board(Options *options);
  ~Board();

  bool		alignBreak(Pos pos, Pos dir, PLAYER player);
  bool		isCaseBreakable(Pos pos, PLAYER player);
  int		getAlignement(Pos pos, Pos dir, PLAYER player, bool checkBreakable);
  void		delEatenPieces(Pos del, Pos del2, Pos allied, PLAYER player);
  bool		move(Pos pos, PLAYER player);
  void		eats(Pos pos, PLAYER player);
  bool		doubleThreeRule(Pos pos, PLAYER player);
  bool		isWinner();
  void		addScore(PLAYER player);
  int**		getBoard();

  int		operator[](Pos pos);

  private:

  unsigned int			_size;
  int				**_board;
  Pos				_lastMove;
  PLAYER			_lastPlayer;
  Pos				_dir[4];
  int				_score[2];
};

#endif /* !BOARD_H_ */
