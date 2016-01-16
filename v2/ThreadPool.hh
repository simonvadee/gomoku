#ifndef THREADPOOL_HH_
# define THREADPOOL_HH_

# include <vector>

class					ThreadPool
{
public:
  ThreadPool();
  ~ThreadPool();

private:
  std::vector<UThread*>			_pool;
  
public:
  void					initPool();
  void					startPool();
  void					stopPool();

private:
  
};

#endif
