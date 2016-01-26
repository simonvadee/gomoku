#ifndef GUI_HH_
# define GUI_HH_

# include <SFML/Graphics.hpp>
# include <vector>
# include "Board.hh"

# define MAP 800

class				Gui
{
public:
  Gui();
  ~Gui();

private:
  sf::RenderWindow		_window;
  Options*			_options;
  int				_rules;
  Board*			_board;
  int				_itemMargin;
  int				_itemOffset;
  int				_itemSize;
  float				_pawnSize;
  int				_rowSize;
  int				_mapSize;
  TIME				_time;
  sf::Color			_color1;
  sf::Color			_color2;
  std::vector<sf::Color>*	_colors;
  sf::Font			_font;
  sf::Text			_sizeD;
  sf::RectangleShape		_sizeR;
  sf::RectangleShape		_rowShape;
  sf::RectangleShape		_colShape;
  sf::RectangleShape		_pawn;
  Pos				_hitPos;

public:
  void				setBoard(Board* board);
  void				gameDisplay();
  void				updateDisplay();
  Pos&				gameListener();
  Options*			displayMenu();
  void				setWinner(PLAYER pl);
  void				displayScore(PLAYER play, int scores[2]);

private:
  void				chooseRandColors();
  void				displayGrid();
  void				setMenuButtons();
  void				setRulesButtons();
  void				setTimeButtons();
};

#endif
