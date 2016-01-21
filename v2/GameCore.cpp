#include "GameCore.hh"
#include <unistd.h>
GameCore::GameCore()
  : _gui(new Gui())
{
  Rules::instanciateRules();
  while (1)
    {
      initMenu();
      initGame();
    }
}

GameCore::~GameCore()
{
}

bool			GameCore::initMenu()
{
  _options = _gui->displayMenu();
}

bool			GameCore::initGame()
{
  Rules::setSize(_options->size);
  _board = new Board();

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
      delete _shared;
      delete _pool;
    }
}

void			GameCore::startGame(Player* p1, Player* p2)
{
  PLAYER	turn = PLAYER1;

  while (true)
    {
      p1->play();
      if (_board->isWinner())
	{
	  _gui->setWinner(PLAYER1);
	  return ;
	}
      p2->play();
      if (_board->isWinner())
	{
	  _gui->setWinner(PLAYER1);
	  return ;
	}
    }
}
