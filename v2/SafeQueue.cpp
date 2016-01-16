#include "SafeQueue.hh"

SafeQueue::SafeQueue()
  : _stockMutex(new UMutex()),
    _processedMutex(new UMutex()),
    _stock(new std::vector<std::pair<char**, Pos>*>()),
    _processed(new std::vector<std::pair<int, Pos>*>())
{
}

SafeQueue::~SafeQueue()
{
  delete (_stockMutex);
  delete (_processedMutex);
  delete (_stock);
  delete (_processed);
}

std::pair<char**, Pos>*		SafeQueue::popStock()
{
  if (_stock->empty())
    return NULL;

  ScopedLock			scope(_stockMutex);
  std::pair<char**, Pos>*	buff;

  buff = _stock->back();
  _stock->pop_back();
  return (buff);
}

std::pair<int, Pos>*		SafeQueue::popProcessed()
{
  if (_processed->empty())
    return NULL;

  ScopedLock			scope(_processedMutex);
  std::pair<int, Pos>*		buff;

  buff = _processed->back();
  _processed->pop_back();
  return (buff);
}

void				SafeQueue::fillStock(std::pair<char**, Pos>* map)
{
  ScopedLock			scope(_stockMutex);

  _stock->push_back(map);
}

void				SafeQueue::fillProcessed(std::pair<int, Pos>* res)
{
  ScopedLock			scope(_processedMutex);

  _processed->push_back(res);
}
