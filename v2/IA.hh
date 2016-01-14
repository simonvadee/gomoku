#ifndef IA_H_
# define IA_H_

# include "Player.hh"

class IA : public Player
{
public:
  IA(Board *board, Gui *gui, PLAYER player);
  ~IA();

  bool		play();

private:

};

#endif /* !IA_H_ */
