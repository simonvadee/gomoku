#include <unistd.h>
#include "GameCore.hh"
#include "Exceptions.hpp"

GameCore::GameCore()
  : _gui(new Gui())
{
  std::srand(std::time(NULL));
  Rules::instanciateRules();
  while (1)
    {
      try
	{
	  initMenu();
	  initGame();
	}
      catch (Exceptions::EndGameExcept e)
	{
	  std::cerr << e.what() << std::endl;
	  break ;
	}
      catch (Exceptions::ErrorExcept e)
	{
	  std::cerr << e.what() << std::endl;
	  break ;
	}
    }
}

GameCore::~GameCore()
{
  if (_pool)
    delete _pool;
  if (_shared)
    delete _shared;
}

bool			GameCore::initMenu()
{
  _options = _gui->displayMenu();
}

bool			GameCore::initGame()
{
  Rules::setSize(_options->size);

  _board = new Board;
  _board->cleanMap();
  _gui->setBoard(_board);
  _gui->updateDisplay();
  if (_options->rules == PVM || _options->rules == MVM)
    {
      _shared = new SafeQueue();
      _pool = new ThreadPool(MAX_THREAD, _shared, static_cast<unsigned int>(_options->size), _board->getBoard());
      _pool->startPool();
    }
  switch (_options->rules)
    {
    case PVP:
      startGame(new Human(_board, _gui, PLAYER1), new Human(_board, _gui, PLAYER2));
      break;
    case PVM:
      startGame(new Human(_board, _gui, PLAYER1), new IA(_board, _gui, PLAYER2, _shared));
      break;
    case MVM:
      startGame(new IA(_board, _gui, PLAYER1, _shared), new IA(_board, _gui, PLAYER2, _shared));
      break;
    }
  if (_options->rules == PVM || _options->rules == MVM)
    {
      delete _pool;
      delete _shared;
    }
  delete _board;
}

void			GameCore::startGame(Player* p1, Player* p2)
{
  PLAYER	turn = static_cast<PLAYER>(std::rand() % 2 + 1);

  while (true)
    {
      if (turn == PLAYER::PLAYER1 && p1->play() && _board->isWinner())
	{
	  _gui->displayScore(turn, _board->getScore());
	  _gui->setWinner(PLAYER1);
	  return ;
	}
      else if (turn == PLAYER::PLAYER2 && p2->play() && _board->isWinner())
	{
	  _gui->displayScore(turn, _board->getScore());
	  _gui->setWinner(PLAYER2);
	  return ;
	}
      _gui->optionsChanged();
      _gui->displayScore(turn, _board->getScore());
      turn = (turn == PLAYER1 ? PLAYER::PLAYER2 : PLAYER::PLAYER1);
    }
}
