#include <SFML/Graphics.hpp>
#include "Gui.hh"

Gui::Gui()
  : _mapSize(19),
    _window(sf::VideoMode(MAP, MAP), "GOMOKU")
{
  //      sf::Event event;
  // while (_window.pollEvent(event));
  _window.setFramerateLimit(30);  // gameDisplay();
}

Gui::~Gui()
{
}

Pos&			Gui::gameListener()
{
  int** grid = _board->getBoard();

  while (_window.isOpen())
    {
      sf::Event event;
      while (_window.pollEvent(event))
	{
	  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	    {
	      sf::Vector2i p = sf::Mouse::getPosition(_window);
	      if (p.x >= 0 && p.x / _pawnSize < _mapSize && p.y >= 0 && p.y / _pawnSize < _mapSize)
		{
		  _hitPos.x = static_cast<int>(static_cast<float>(p.x) / _pawnSize);
		  _hitPos.y = static_cast<int>(static_cast<float>(p.y) / _pawnSize);
		  return _hitPos;
		}
	    }
	  if (event.type == sf::Event::Closed)
	    _window.close();
	}
    }
  throw ("");
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
	    {
	      _pawn.setPosition(_pawnSize * i, _pawnSize * j);
	      _window.draw(_pawn);
	    }
  	}
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
