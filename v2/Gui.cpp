#include <SFML/Graphics.hpp>
#include "Gui.hh"

Gui::Gui()
  : _mapSize(19),
    _window(sf::VideoMode(800, 800), "GOMOKU")
{
  gameDisplay();
}

Gui::~Gui()
{
}

void			Gui::gameDisplay()
{
   // while (_window.isOpen())
   //   {
  sf::Event event;
  while (_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	_window.close();
    }
  // }
  return ;
}

void			Gui::setBoard(Board* board)
{
  _board = board;
  _pawnSize = (MAP / _mapSize);
  _rowSize = MAP / _mapSize / 10;
  _rowShape = sf::RectangleShape(sf::Vector2f(MAP, _rowSize));
  _colShape = sf::RectangleShape(sf::Vector2f(_rowSize, MAP));
  _pawn = sf::RectangleShape(sf::Vector2f(_pawnSize * 0.8f, _pawnSize * 0.8f));
}

void			Gui::updateDisplay()
{
  // std::cout << "loooool pawnsize" << _pawnSize << "  " << std::endl;
  // sf::RectangleShape pawn(sf::Vector2f(40, 40));
  // pawn.setFillColor(sf::Color::Red);
  
  // pawn.setPosition(40, 40);
  
  // _window.draw(pawn);
  // _window.display();  
  // std::cout << "loooool pawnsize" << _pawnSize << "  " << std::endl;



  int** grid = _board->getBoard();
  _window.clear();
  displayGrid();
  for (int i = 0; i < _mapSize; ++i)
    {
      for (int j = 0; j < _mapSize; ++j)
  	{
  	  if (grid[i][j] == 1)
	    _pawn.setFillColor(sf::Color::Green);
	  else if (grid[i][j] == 2)
	    _pawn.setFillColor(sf::Color::Red);
	  
	  if (grid[i][j] != 0)
	      _pawn.setPosition(_pawnSize * j, _pawnSize * i);	  
	      _window.draw(_pawn);
	    }
  	}
      _window.display();  
    }
  _window.display();  
}

void			Gui::displayGrid()
{
  for (int i = 0; i < _mapSize; ++i)
    {
      _rowShape.setPosition(0, _pawnSize / 2 - _rowSize + _pawnSize * i);
      _window.draw(_rowShape);
      _colShape.setPosition(_pawnSize / 2 - _rowSize + _pawnSize * i, 0);
      _window.draw(_colShape);
    }
}
