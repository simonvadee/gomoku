#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

# include <vector>
# include "UThread.hh"

class					ThreadPool
{
public:
  ThreadPool(int maxThread, SafeQueue* safe, unsigned int mapSize, char **map);
  ~ThreadPool();

private:
  SafeQueue*				_safe;
  std::vector<UThread*>*		_pool;
  
public:
  void					initPool(void routine(SafeQueue* safe, unsigned int mapSize, char **map));
  void					startPool();
  void					stopPool();
};

#endif
