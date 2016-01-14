#ifndef GAMECORE_HH_
# define GAMECORE_HH_

# include "Gui.hh"
# include "Board.hh"
# include "Human.hh"
# include "IA.hh"

class			GameCore
{
public:
  GameCore();
  ~GameCore();
  
private:
  Options*		_options;
  Gui*			_gui;
  Board*		_board;
  
public:
  bool			initMenu();
  bool			initGame();
  void			startGame(Player* p1, Player* p2);
};

#endif
