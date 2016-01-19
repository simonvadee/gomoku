#ifndef UTHREAD_H_
# define UTHREAD_H_

# include <thread>
# include <string>
# include "SafeQueue.hh"
# include "UMutex.hh"

class UThread
{
public:
  UThread(SafeQueue* safe, unsigned int mapSize);
  ~UThread();

 private:
  SafeQueue*		_stock;
  std::thread*		_thread;
  unsigned int		_mapSize;

  void			(*_routine)(SafeQueue* safe, unsigned int mapSize);

 public:
  bool			InitThread(void routine(SafeQueue* safe, unsigned int mapSize));
  bool			StartThread();
  bool			WaitThread();
  void			DestroyThread();
};

#endif
