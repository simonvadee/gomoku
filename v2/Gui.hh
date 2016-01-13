#ifndef GUI_HH_
# define GUI_HH_

# include <SFML/Graphics.hpp>
# include "Board.hh"

# define MAP 800

class			Gui
{
public:
  Gui();
  ~Gui();

private:
  Board*		_board;
  float			_pawnSize;
  int			_rowSize;
  int			_mapSize;
  sf::RenderWindow	_window;
  sf::RectangleShape	_rowShape;
  sf::RectangleShape	_colShape;
  sf::RectangleShape	_pawn;

public:
  void			setBoard(Board* board);
  void			gameDisplay();
  void			updateDisplay();

private:
  void			displayGrid();
};

#endif
