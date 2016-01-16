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

class Rules
{
private :
  static Rules* _rules;

public :
  int	_rulesMask;

private :
  Rules(int);
  ~Rules();

public :
  static void	instanciateRules();
  static void	destroyRules();
  static void	setRules(int);
  static int	getRules();
};

class Board
{
public:
  Board();
  ~Board();
  const static unsigned int	_size = 19;

private:
  char**			_board;
  Pos				_lastMove;
  PLAYER			_lastPlayer;
  int				_score[2];
  bool				_breakable;
  bool				_eatable;

  bool				checkNeighbours(std::string line, int index, PLAYER player, Pos key, Pos size);
  bool				checkDoubleThree(PLAYER player, Pos key, int lineChecked,  std::string data[4]);


public:
  static bool	validPos(Pos pos);
  static bool	alignBreak(char **map, Pos pos, Pos dir, PLAYER player);
  static bool	isCasePlayable(char **map, Pos pos, PLAYER player);
  static bool	isCaseBreakable(char **map, Pos pos, PLAYER player);
  static int	getAlignement(char **map, Pos pos, Pos dir, PLAYER player, bool checkBreakable);
  static bool	canEatPieces(char **map, Pos del1, Pos del2, Pos allied, PLAYER player);
  void		delEatenPieces(Pos del, Pos del2, Pos allied, PLAYER player);
  bool		move(Pos pos, PLAYER player);
  void		eats(Pos pos, PLAYER player);
  static bool	doubleThreeRule(Pos pos, PLAYER player, int lineChecked);
  bool		isWinner();
  void		addScore(PLAYER player);
  char**	getBoard();
  void		cleanMap();
  unsigned int	getSize() const;

  int		operator[](Pos pos);
};

#endif /* !BOARD_H_ */
