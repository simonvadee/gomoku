#ifndef GUI_HH_
# define GUI_HH_

# include <SFML/Graphics.hpp>
# include "Board.hh"

# define MAP 1500

class			Gui
{
public:
  Gui();
  ~Gui();

private:
  sf::RenderWindow	_window;
  Options*		_options;
  int			_rules;
  Board*		_board;
  int			_itemMargin;
  int			_itemOffset;
  int			_itemSize;
  float			_pawnSize;
  int			_rowSize;
  int			_mapSize;
  sf::Text		_sizeD;
  sf::RectangleShape	_sizeR;
  sf::RectangleShape	_rowShape;
  sf::RectangleShape	_colShape;
  sf::RectangleShape	_pawn;
  Pos			_hitPos;

public:
  void			setBoard(Board* board);
  void			gameDisplay();
  void			updateDisplay();
  Pos&			gameListener();
  Options*		displayMenu();

private:
  void			displayGrid();
  void			setMenuButtons();
  void			setRulesButtons();
};

#endif
