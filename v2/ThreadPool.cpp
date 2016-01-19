#include "ThreadPool.hh"
#include "MinMax.hh"

void				routine(SafeQueue* shared, unsigned int mapSize, char **map);

ThreadPool::ThreadPool(int maxThread, SafeQueue* safe, unsigned int mapSize, char **map)
  : _pool(new std::vector<UThread*>()), _safe(safe)
{
  for (int i = 0; i < maxThread; ++i)
    _pool->push_back(new UThread(safe, mapSize, map));
  initPool(routine);
}

ThreadPool::~ThreadPool()
{
  _safe->setGameRunning(false);
  for (std::vector<UThread*>::iterator it = _pool->begin(); it != _pool->end(); ++it)
    (*it)->DestroyThread();
  delete _pool;
}

void				ThreadPool::initPool(void routine(SafeQueue* safe, unsigned int mapSize, char **map))
{
  for (std::vector<UThread*>::iterator it = _pool->begin(); it != _pool->end(); ++it)
    (*it)->InitThread(routine);
}

void				ThreadPool::startPool()
{
  for (std::vector<UThread*>::iterator it = _pool->begin(); it != _pool->end(); ++it)
    (*it)->StartThread();
}

void				ThreadPool::stopPool()
{
  for (std::vector<UThread*>::iterator it = _pool->begin(); it != _pool->end(); ++it)
    (*it)->WaitThread();
}

void				routine(SafeQueue* shared, unsigned int mapSize, char **map)
{
  MinMax*			thread = new MinMax(shared, mapSize, map);
}
