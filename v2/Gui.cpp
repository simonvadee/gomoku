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
//   sf::CircleShape shape();
//   int_board.getBoard();
//   _window.clear();
//   for (int i = 0; i < _size; ++i)
//     {
//       for (int i = 0; i < _size; ++i)
// 	{
// 800 / _size
// 	}
//     }
//   _window.display();  
}
