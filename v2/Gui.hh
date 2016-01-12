#ifndef GUI_HH_
# define GUI_HH_

# include <SFML/Graphics.hpp>
# include "Board.hh"

# define MAPX 800
# define MAPY 800

typedef struct
{
  unsigned int size;
  int rules;
}		Options;

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
  void			setBoard(Board* board);
  void			gameDisplay();
  void			updateDisplay();
};

#endif
