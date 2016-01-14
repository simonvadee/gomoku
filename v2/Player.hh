#ifndef PLAYER_H_
# define PLAYER_H_

#include "Board.hh"
#include "Gui.hh"

class Player
{
public:

  Player(Board *board, Gui* gui, PLAYER player);
  ~Player() {};

  virtual bool		play() = 0;

 protected:

  Board*	_board;
  Gui*		_gui;
  PLAYER	_id;
};

#endif /* !PLAYER_H_ */
