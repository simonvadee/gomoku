#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <cstdlib>
#include "Gui.hh"
#include "Exceptions.hpp"

Gui::Gui()
  : _window(sf::VideoMode(MAP + MAP * 0.2, MAP + MAP * 0.25), "GOMOKU"),
    _options(new Options),
    _rules(0xfff0),
    _time(TIME::T50)
{
  if (!_font.loadFromFile("arial.ttf"))
    {
      throw Exceptions::EndGameExcept("GameOver");
    }

  chooseRandColors();
  _window.setFramerateLimit(30);
  _itemOffset = 2 * MAP / 5;
  _itemSize = MAP / 5;
  _itemMargin = MAP / 6;
  _options->size = 15;
  _sizeR = sf::RectangleShape(sf::Vector2f(_itemSize, _itemSize / 2));
  _sizeR.setFillColor(sf::Color(220, 180, 190));
  Rules::instanciateRules();
  Rules::setTime(_time);
}

Gui::~Gui()
{
  Rules::destroyRules();
  delete _options;
}

void			Gui::chooseRandColors()
{
  int			r = (std::rand() + 10) % 255;
  int			g = (std::rand() + 10) % 255;
  int			b = (std::rand() + 10) % 255;

  _light1 = sf::Color(r, g, b);
  _light2 = sf::Color(255 - r, 255 - g, 255 - b);
  _color1 = sf::Color((r - 40 > 0 ? r - 40 : 0), (g - 40 > 0 ? g - 40 : 0), (b - 40 > 0 ? b - 40 : 0));
  _color2 = sf::Color((255 - r - 40 > 0 ? 255 - r - 40 : 0), (255 - g - 40 > 0 ? 255 - g - 40 : 0), (255 - b - 40 > 0 ? 255 - b - 40 : 0));
  _outl1 = sf::Color((r - 60 > 0 ? r - 60 : 0), (g - 60 > 0 ? g - 60 : 0), (b - 60 > 0 ? b - 60 : 0));
  _outl2 = sf::Color((255 - r - 60 > 0 ? 255 - r - 60 : 0), (255 - g - 60 > 0 ? 255 - g - 60 : 0), (255 - b - 60 > 0 ? 255 - b - 60 : 0));
}

Options*		Gui::displayMenu()
{
  setMenuButtons();
  setMenuButtons();
  while (_window.isOpen())
    {
      while (_window.pollEvent(_event))
	{
	  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	    {
	      sf::Vector2i p = sf::Mouse::getPosition(_window);
	      if (p.x >= _itemOffset && p.x < _itemOffset + _itemSize && p.y >= _itemMargin && p.y < _itemMargin + _itemSize / 2)
		{
		  _options->rules = PVP;
		  return _options;
		}
	      else if (p.x >= _itemOffset && p.x < _itemOffset + _itemSize && p.y >= 2 * _itemMargin && p.y < 2 * _itemMargin + _itemSize / 2)
		{
		  _options->rules = PVM;
		  return _options;
		}
	      else if (p.x >= _itemOffset && p.x < _itemOffset + _itemSize && p.y >= 3 * _itemMargin && p.y < 3 * _itemMargin + _itemSize / 2)
		{
		  _options->rules = MVM;
		  return _options;
		}
	      else if (p.x >= _itemOffset && p.x < _itemOffset + _itemSize && p.y >= 4 * _itemMargin && p.y < 4 * _itemMargin + _itemSize / 2)
		{
		  if (_options->size < 19)
		    ++(_options->size);
		  setMenuButtons();
		}
	      else if (p.x >= _itemOffset && p.x < _itemOffset + _itemSize && p.y >= 5 * _itemMargin && p.y < 5 * _itemMargin + _itemSize / 2)
		{
		  if (_options->size > 5)
		    --(_options->size);
		  setMenuButtons();
		}
	      else if (p.x >= MAP * 4 / 5 + _itemSize && p.x < MAP * 4 / 5 + _itemSize + _itemSize / 2
		       && p.y >= 3 * _itemMargin && p.y < 3 * _itemMargin + _itemSize / 2
		       || p.x >= MAP * 4 / 5 + _itemSize && p.x < MAP * 4 / 5 + _itemSize + _itemSize / 2
		       && p.y >= 4 * _itemMargin && p.y < 4 * _itemMargin + _itemSize / 2
		       )
		{
		  chooseRandColors();
		  setMenuButtons();
		}
	    }
	  if (_event.type == sf::Event::Closed)
	    _window.close();
	}
      sf::sleep(sf::milliseconds(30));
    }
  throw Exceptions::EndGameExcept("GameOver");
}

Pos&			Gui::gameListener()
{
  while (_window.isOpen())
    {
      while (_window.pollEvent(_event))
	{
	  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	    {
	      sf::Vector2i p = sf::Mouse::getPosition(_window);
	      if (p.x >= 0 && p.x / _pawnSize < _options->size && p.y >= 0 && p.y / _pawnSize < _options->size)
		{
		  _hitPos.x = static_cast<int>(static_cast<float>(p.x) / _pawnSize);
		  _hitPos.y = static_cast<int>(static_cast<float>(p.y) / _pawnSize);
		  return _hitPos;
		}
	      buttonListener(p);
	    }
	  if (_event.type == sf::Event::Closed)
	    _window.close();
	}
      sf::sleep(sf::milliseconds(30));
    }
  throw Exceptions::EndGameExcept("GameOver");
}

void			Gui::optionsChanged()
{
  sf::Event event;
  while (_window.pollEvent(_event))
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	  sf::Vector2i p = sf::Mouse::getPosition(_window);
	  buttonListener(p);
	}
      if (_event.type == sf::Event::Closed)
	{
	  _window.close();
	  throw Exceptions::EndGameExcept("GameOver");  
	}
    }
}

void			Gui::buttonListener(sf::Vector2i& p)
{
  if (p.x >= _itemSize / 5 && p.y >= MAP + MAP * 0.1 && p.x < _itemSize / 5 + _itemSize && p.y < MAP + MAP * 0.1 + _itemSize / 2)
   {
     _board->cleanMap();
     updateDisplay();
   }
 else if (p.x >= _itemSize * 1.2 + _itemSize / 5 && p.y >= MAP + MAP * 0.1 && p.x < _itemSize * 1.2 + _itemSize / 5 + _itemSize && p.y < MAP + MAP * 0.1 + _itemSize / 2)
   {
     if (_rules & RULE_THREE)
       _rules -= RULE_THREE;
     else
       _rules += RULE_THREE;
     Rules::setRules(_rules);
     updateDisplay();
   }
 else if (p.x >= _itemSize * 2.4 + _itemSize / 5 && p.y >= MAP + MAP * 0.1 && p.x < _itemSize * 2.4 + _itemSize / 5 + _itemSize && p.y < MAP + MAP * 0.1 + _itemSize / 2)
   {
     if (_rules & RULE_BREAK)
       _rules -= RULE_BREAK;
     else
       _rules += RULE_BREAK;
     Rules::setRules(_rules);
     updateDisplay();
   }
 else if (p.x >= _itemSize * 3.6 + _itemSize / 5 && p.y >= MAP + MAP * 0.1 && p.x < _itemSize * 3.6 + _itemSize / 5 + _itemSize && p.y < MAP + MAP * 0.1 + _itemSize / 2)
   {
     if (_rules & RULE_EAT)
       _rules -= RULE_EAT;
     else
       _rules += RULE_EAT;
     Rules::setRules(_rules);
     updateDisplay();
   }
 else if (p.x >= MAP + _itemSize / 5 && p.y >= MAP * 0.2 && p.x < MAP + _itemSize / 5 + _itemSize / 2 && p.y < MAP * 0.2 + _itemSize / 2)
   {
     _time = TIME::T50;
     Rules::setTime(_time);
     updateDisplay();
   }
 else if (p.x >= MAP + _itemSize / 5 && p.y >= MAP * 0.4 && p.x < MAP + _itemSize / 5 + _itemSize / 2 && p.y < MAP * 0.4 + _itemSize / 2)
   {
     _time = TIME::T20;
     Rules::setTime(_time);
     updateDisplay();
   }
 else if (p.x >= MAP + _itemSize / 5 && p.y >= MAP * 0.6 && p.x < MAP + _itemSize / 5 + _itemSize / 2 && p.y < MAP * 0.6 + _itemSize / 2)
   {
     _time = TIME::T10;
     Rules::setTime(_time);
     updateDisplay();
   }
 else if (p.x >= MAP + _itemSize / 5 && p.y >= MAP * 0.8 && p.x < MAP + _itemSize / 5 + _itemSize / 2 && p.y < MAP * 0.8 + _itemSize / 2)
   {
     _time = TIME::SUPERBRAIN;
     Rules::setTime(_time);
     updateDisplay();
   }
}

void			Gui::setBoard(Board* board)
{
  _board = board;
  _pawnSize = (MAP / _options->size);
  _rowSize = MAP / _options->size / 10;
  _rowShape = sf::RectangleShape(sf::Vector2f(MAP, _rowSize));
  _colShape = sf::RectangleShape(sf::Vector2f(_rowSize, MAP));
  _pawn = sf::CircleShape(_pawnSize * 0.4f);
  _outline = sf::CircleShape(_pawnSize * 0.47f);
  _light = sf::CircleShape(_pawnSize * 0.2f);
}

void			Gui::updateDisplay()
{
  char** grid = _board->getBoard();

  _window.clear();
  setRulesButtons();
  setTimeButtons();
  displayGrid();
  for (int i = 0; i < _options->size; ++i)
    {
      for (int j = 0; j < _options->size; ++j)
  	{
  	  if (grid[i][j] == PLAYER::PLAYER1)
	    {
	      _pawn.setFillColor(_color1);
	      _outline.setFillColor(_outl1);
	      _light.setFillColor(_light1);
	    }
	  else if (grid[i][j] == PLAYER::PLAYER2)
	    {
	      _pawn.setFillColor(_color2);
	      _outline.setFillColor(_outl2);
	      _light.setFillColor(_light2);
	    }
	  if (grid[i][j] != 0)
	    {
	      _pawn.setPosition(_pawnSize * i, _pawnSize * j);
	      _outline.setPosition(_pawnSize * i, _pawnSize * j);
	      _light.setPosition(_pawnSize * i + _pawnSize / 11, _pawnSize * j + _pawnSize / 11);
	      _window.draw(_outline);
	      _window.draw(_pawn);
	      _window.draw(_light);
	    }
  	}
    }
  _window.display();
}

void			Gui::displayGrid()
{
  for (int i = 0; i < _options->size; ++i)
    {
      _rowShape.setPosition(0, _pawnSize / 2 - _rowSize + _pawnSize * i);
      _window.draw(_rowShape);
      _colShape.setPosition(_pawnSize / 2 - _rowSize + _pawnSize * i, 0);
      _window.draw(_colShape);
    }
}

void			Gui::setWinner(PLAYER pl)
{
  sf::Text		*text = new sf::Text();
  std::string		str = "Player " + std::to_string(pl) + " wins !!";

  text->setFont(_font);
  text->setCharacterSize(50);
  text->setColor(sf::Color::White);
  text->setStyle(sf::Text::Bold);

  text->setPosition(MAP / 4, MAP * 2 / 5);
  text->setString(str);
  _window.draw(*text);
  _window.display();
  while (_window.isOpen())
    {
      sf::Event event;
      while (_window.pollEvent(_event))
	{
	  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	    return;
	  if (event.type == sf::Event::Closed)
	    {
	      _window.close();
	      throw Exceptions::EndGameExcept("GameOver");
	    }
	}
    }
}

void			Gui::setMenuButtons()
{
  sf::RectangleShape block(sf::Vector2f(_itemSize, _itemSize / 2));
  sf::Text *text = new sf::Text();

  _window.clear();

  text->setFont(_font);
  block.setFillColor(sf::Color(220, 210, 190));
  text->setCharacterSize(24);
  text->setColor(sf::Color::White);
  text->setStyle(sf::Text::Bold);
  _sizeD.setFont(_font);
  _sizeD.setCharacterSize(24);
  _sizeD.setColor(sf::Color::White);
  _sizeD.setStyle(sf::Text::Bold);

  _sizeR.setPosition(_itemOffset / 3, 4 * _itemMargin);
  _sizeD.setPosition(_itemOffset / 3 + MAP / 20, 4 * _itemMargin + _itemSize / 4);
  _sizeD.setString(std::to_string(_options->size));
  _window.draw(_sizeR);
  _window.draw(_sizeD);

  block.setPosition(_itemOffset, _itemMargin);
  text->setPosition(_itemOffset + MAP / 20, _itemMargin + _itemSize / 4);
  text->setString("PVP");
  _window.draw(block);
  _window.draw(*text);

  block.setPosition(_itemOffset, 2 * _itemMargin);
  text->setPosition(_itemOffset + MAP / 20, 2 * _itemMargin + _itemSize / 4);
  text->setString("PVM");
  _window.draw(block);
  _window.draw(*text);

  block.setPosition(_itemOffset, 3 * _itemMargin);
  text->setPosition(_itemOffset + MAP / 20, 3 * _itemMargin + _itemSize / 4);
  text->setString("MVM");
  _window.draw(block);
  _window.draw(*text);

  block.setPosition(_itemOffset, 4 * _itemMargin);
  text->setPosition(_itemOffset + MAP / 20, 4 * _itemMargin + _itemSize / 4);
  text->setString("+");
  _window.draw(block);
  _window.draw(*text);

  block.setPosition(_itemOffset, 5 * _itemMargin);
  text->setPosition(_itemOffset + MAP / 20, 5 * _itemMargin + _itemSize / 4);
  text->setString("-");
  _window.draw(block);
  _window.draw(*text);

  sf::RectangleShape block2(sf::Vector2f(_itemSize / 2, _itemSize / 2));

  block2.setFillColor(_color1);
  block2.setPosition(MAP * 4 / 5 + _itemSize, 3 * _itemMargin);
  text->setPosition(MAP * 4 / 5, 3 * _itemMargin);
  text->setString("PLAYER 1");
  _window.draw(block2);
  _window.draw(*text);

  block2.setFillColor(_color2);
  block2.setPosition(MAP * 4 / 5 + _itemSize, 4 * _itemMargin);
  text->setPosition(MAP * 4 / 5, 4 * _itemMargin);
  text->setString("PLAYER 2");
  _window.draw(block2);
  _window.draw(*text);

  _window.display();
  delete(text);
}

void			Gui::displayScore(PLAYER play, int scores[2])
{
  sf::Text *		text = new sf::Text();

  text->setFont(_font);
  text->setStyle(sf::Text::Bold);
  text->setCharacterSize(24);
  if (play == PLAYER::PLAYER1)
    text->setColor(sf::Color::Red);
  else
    text->setColor(sf::Color::White);
  text->setPosition(MAP * 2 / 5, MAP);
  text->setString("PLAYER1 : " + std::to_string(scores[0]));
  _window.draw(*text);

  if (play == PLAYER::PLAYER2)
    text->setColor(sf::Color::Red);
  else
    text->setColor(sf::Color::White);
  text->setPosition(MAP * 3 / 5, MAP);
  text->setString("PLAYER2 : " + std::to_string(scores[1]));
  _window.draw(*text);

  _window.display();
  delete (text);
}

void			Gui::setRulesButtons()
{
  sf::RectangleShape	block(sf::Vector2f(_itemSize, _itemSize / 2));
  sf::Text *		text = new sf::Text();

  _window.clear();

  text->setFont(_font);
  block.setFillColor(sf::Color(220, 210, 190));
  text->setCharacterSize(18);
  text->setColor(sf::Color::White);
  text->setStyle(sf::Text::Bold);

  block.setPosition(_itemSize * 0 + _itemSize / 5, MAP + MAP * 0.1);
  text->setPosition(_itemSize * 0 + 2 * _itemSize / 5, MAP + MAP * 0.14);
  text->setString("RESTART");
  _window.draw(block);
  _window.draw(*text);

  if (_rules & RULE_THREE)
    block.setFillColor(sf::Color(20, 200, 6));
  else
    block.setFillColor(sf::Color(200, 20, 6));

  block.setPosition(_itemSize * 1.2 + _itemSize / 5, MAP + MAP * 0.1);
  text->setPosition(_itemSize * 1.2 + 2 * _itemSize / 5, MAP + MAP * 0.14);
  text->setString("2*3 RULE");
  _window.draw(block);
  _window.draw(*text);

  if (_rules & RULE_BREAK)
    block.setFillColor(sf::Color(20, 200, 6));
  else
    block.setFillColor(sf::Color(200, 20, 6));

  block.setPosition(_itemSize * 2.4 + _itemSize / 5, MAP + MAP * 0.1);
  text->setPosition(_itemSize * 2.4 + 2 * _itemSize / 5, MAP + MAP * 0.14);
  text->setString("BREAKABLE");
  _window.draw(block);
  _window.draw(*text);

  if (_rules & RULE_EAT)
    block.setFillColor(sf::Color(20, 200, 6));
  else
    block.setFillColor(sf::Color(200, 20, 6));

  block.setPosition(_itemSize * 3.6 + _itemSize / 5, MAP + MAP * 0.1);
  text->setPosition(_itemSize * 3.6 + 2 * _itemSize / 5, MAP + MAP * 0.14);
  text->setString("EATABLE");
  _window.draw(block);
  _window.draw(*text);
  delete(text);
}

void			Gui::setTimeButtons()
{
  sf::RectangleShape	block(sf::Vector2f(_itemSize / 2, _itemSize / 2));
  sf::Text *		text = new sf::Text();

  text->setFont(_font);
  block.setFillColor(sf::Color(220, 210, 190));
  text->setCharacterSize(18);
  text->setColor(sf::Color::White);
  text->setStyle(sf::Text::Bold);

  if (_time == TIME::T50)
    block.setFillColor(sf::Color(20, 200, 6));
  else
    block.setFillColor(sf::Color(200, 20, 6));

  block.setPosition(MAP + _itemSize / 5, MAP * 0.2);
  text->setPosition(MAP + _itemSize / 4, MAP * 0.2 + _itemSize / 4);
  text->setString("50 ms");
  _window.draw(block);
  _window.draw(*text);

  if (_time == TIME::T20)
    block.setFillColor(sf::Color(20, 200, 6));
  else
    block.setFillColor(sf::Color(200, 20, 6));

  block.setPosition(MAP + _itemSize / 5, MAP * 0.4);
  text->setPosition(MAP + _itemSize / 4, MAP * 0.4 + _itemSize / 4);
  text->setString("20 ms");
  _window.draw(block);
  _window.draw(*text);

  if (_time == TIME::T10)
    block.setFillColor(sf::Color(20, 200, 6));
  else
    block.setFillColor(sf::Color(200, 20, 6));

  block.setPosition(MAP + _itemSize / 5, MAP * 0.6);
  text->setPosition(MAP + _itemSize / 4, MAP * 0.6 + _itemSize / 4);
  text->setString("10 ms");
  _window.draw(block);
  _window.draw(*text);

  if (_time == TIME::SUPERBRAIN)
    block.setFillColor(sf::Color(20, 200, 6));
  else
    block.setFillColor(sf::Color(200, 20, 6));

  block.setPosition(MAP + _itemSize / 5, MAP * 0.8);
  text->setPosition(MAP + _itemSize / 4, MAP * 0.8 + _itemSize / 5);
  text->setString("SUPER\nBRAIN");
  _window.draw(block);
  _window.draw(*text);
}
