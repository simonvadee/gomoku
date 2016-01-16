#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

# include <vector>
# include "UThread.hh"

class					ThreadPool
{
public:
  ThreadPool(int maxThread, SafeQueue* safe);
  ~ThreadPool();

private:
  std::vector<UThread*>*		_pool;
  int					_maxThread;
  
public:
  void					initPool(void routine(SafeQueue* safe));
  void					startPool();
  void					stopPool();
};

#endif
