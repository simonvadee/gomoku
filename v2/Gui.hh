#ifndef GUI_HH_
# define GUI_HH_

# include <SFML/Graphics.hpp>
# include "Board.hh"

# define MAP 800

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
  float			_pawnSize;
  int			_rowSize;
  int			_mapSize;
  sf::RenderWindow	_window;
  sf::RectangleShape	_rowShape;
  sf::RectangleShape	_colShape;
  sf::RectangleShape	_pawn;
  Pos			_hitPos;

public:
  void			setBoard(Board* board);
  void			gameDisplay();
  void			updateDisplay();
  void			gameListener();

private:
  void			displayGrid();
};

#endif
