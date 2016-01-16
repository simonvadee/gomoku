#include "ThreadPool.hh"

ThreadPool::ThreadPool(int maxThread, SafeQueue* safe)
  : _pool(new std::vector<UThread*>()), _maxThread(maxThread)
{
  for (int i = 0; i < _maxThread; ++i)
    _pool->push_back(new UThread(safe));
}

ThreadPool::~ThreadPool()
{
  for (std::vector<UThread*>::iterator it = _pool->begin(); it != _pool->end(); ++it)
    (*it)->DestroyThread();
  delete _pool;
}

void				ThreadPool::initPool(void routine(SafeQueue* safe))
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
