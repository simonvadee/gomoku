#include "GameCore.hh"

GameCore::GameCore()
  : _gui(new Gui()), _shared(new SafeQueue())
{
  // options = gui->menu();
  // Board *board = new Board(options->size, options->rules);
  // launchGame(board, new Human(board, gui), new IA(board, gui), gui);
  initMenu();
  initGame();
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
  _board = new Board(_options->size);

  _gui->setBoard(_board);
  _gui->updateDisplay();
  if (_options->rules == PVM || _options->rules == MVM)
    {
      _pool = new ThreadPool(MAX_THREAD, _shared, static_cast<unsigned int>(_options->size), _board->getBoard());
      _pool->startPool();
    }
  switch (_options->rules)
    {
    case PVP:
      startGame(new Human(_board, _gui, PLAYER1), new Human(_board, _gui, PLAYER2));
    case PVM:
      startGame(new Human(_board, _gui, PLAYER1), new IA(_board, _gui, PLAYER2, _shared));
    case MVM:
      startGame(new IA(_board, _gui, PLAYER1, _shared), new IA(_board, _gui, PLAYER2, _shared));
    }
  if (_options->rules == PVM || _options->rules == MVM)
    delete _pool;
}

void			GameCore::startGame(Player* p1, Player* p2)
{
  PLAYER	turn = PLAYER1;

  while (true)
    {
      p1->play();
      if (_board->isWinner())
  	std::cout << "PLAYER 1 WINS !" << std::endl;

      p2->play();
      if (_board->isWinner())
  	std::cout << "PLAYER 1 WINS !" << std::endl;
    }
}
