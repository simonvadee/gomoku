#ifndef UTHREAD_H_
# define UTHREAD_H_

# include <thread>
# include <string>
# include "SafeQueue.hh"
# include "UMutex.hh"

class UThread
{
public:
  UThread(SafeQueue* safe, unsigned int mapSize, char** map);
  ~UThread();

 private:
  SafeQueue*		_stock;
  std::thread*		_thread;
  unsigned int		_mapSize;
  char**		_map;
  void			(*_routine)(SafeQueue* safe, unsigned int mapSize, char **map);

 public:
  bool			InitThread(void routine(SafeQueue* safe, unsigned int mapSize, char **map));
  bool			StartThread();
  bool			WaitThread();
  void			DestroyThread();
};

#endif
