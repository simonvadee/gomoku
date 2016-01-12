#include "Gui.hh"

Gui::Gui()
  : _window(sf::VideoMode(800, 800), "GOMOKU")
{
  gameDisplay();
}

Gui::~Gui()
{
}

void			Gui::gameDisplay()
{
   while (_window.isOpen())
     {
       sf::Event event;
   sf::CircleShape shape(100.f);

   shape.setFillColor(sf::Color::Green);
       while (_window.pollEvent(event))
	 {
	   if (event.type == sf::Event::Closed)
	     _window.close();
	 }
       _window.draw(shape);
     }
   return ;
}

void			Gui::setBoard(Board* board)
{
  _board = board;
}

void			Gui::updateDisplay()
{
  sf::RectangleShape shape(sf::Vector2f(MAP / _size, MAP / _size));
  std::vector<int> *grid = _board->getBoard();
  _window.clear();
  for (int i = 0; i < _size; ++i)
    {
      for (int j = 0; j < _size; ++j)
	{
	  shape.setFillColor(sf::Color::Green);
	  shape.setPosition((MAP / _size) * j, (MAP / _size) * i);
	  _window.draw(shape);	  
	}
    }
  _window.display();  
}
