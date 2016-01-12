#ifndef PLAYER_H_
# define PLAYER_H_

#include "Board.hh"
#include "Gui.hh"

typedef enum
  {
    PLAYER1 = 1,
    PLAYER2
  } PLAYER;

class Player
{
public:

  Player(Board *board, Gui* gui);
  ~Player() {};

  virtual bool		play() = 0;

 private:

  Board*	_board;
  Gui*		_gui;
  // gui

};

#endif /* !PLAYER_H_ */
