#ifndef IA_H_
# define IA_H_

# include "Player.hh"

class IA : public Player
{
public:
  IA(Board *board, Gui *gui, PLAYER player);
  ~IA();

  Pos		minmax();
  bool		play();

private:
  int		_recursionNumber;

};

#endif /* !IA_H_ */
