#ifndef HUMAN_H_
# define HUMAN_H_

# include "Player.hh"

class Human : public Player
{
public:
  Human(Board *board, Gui *gui, PLAYER player);
  ~Human();

  bool		play();

private:

};

#endif /* !HUMAN_H_ */
