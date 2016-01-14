#ifndef BOARD_H_
# define BOARD_H_

# include <iostream>
# include <utility>
# include <vector>

# define OPPONENT(x) (3 - x)

# define RULE_THREE 0xf000
# define RULE_BREAK 0x0f00
# define RULE_EAT 0x00f0

typedef enum
  {
    PLAYER1 = 1,
    PLAYER2
  } PLAYER;

typedef enum
  {
    PVP,
    PVM,
    MVM
  }	MODE;

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
  MODE		rules;
}		Options;

typedef struct
{
  char		x;
  char		y;
}		Pos;

class Board
{
public:
  Board(int size);
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
  void		setRules(int rules);
  char**	getBoard();

  int		operator[](Pos pos);

  private:
  unsigned int			_size;
  char				**_board;
  Pos				_lastMove;
  PLAYER			_lastPlayer;
  Pos				_dir[4];
  int				_score[2];
  int				_rules;
  bool				_breakable;
  bool				_eatable;
};

#endif /* !BOARD_H_ */
