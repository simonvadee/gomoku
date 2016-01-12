#ifndef GUI_HH_
# define GUI_HH_

# include <SFML/Graphics.hpp>
# include "Board.hh"

class			Gui
{
public:
  Gui();
  ~Gui();

private:
  Board*		_board;
  int			_size;
  sf::RenderWindow	_window;

public:
  void			setBoard(Board* board, int size);
  void			gameDisplay();
  void			updateDisplay();
};

#endif
