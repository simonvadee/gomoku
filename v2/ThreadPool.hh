#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

# include <vector>
# include "UThread.hh"

class					ThreadPool
{
public:
  ThreadPool(int maxThread, SafeQueue* safe, unsigned int mapSize);
  ~ThreadPool();

private:
  SafeQueue*				_safe;
  std::vector<UThread*>*		_pool;
  int					_maxThread;
  
public:
  void					initPool(void routine(SafeQueue* safe, unsigned int mapSize));
  void					startPool();
  void					stopPool();
};

#endif
