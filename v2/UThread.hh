#ifndef UTHREAD_H_
# define UTHREAD_H_

# include <thread>
# include <string>
# include "SafeQueue.hh"
# include "UMutex.hh"

class UThread
{
public:
  UThread(SafeQueue* safe);
  ~UThread();

 private:
  SafeQueue*		_stock;
  std::thread*		_thread;

  void			(*_routine)(SafeQueue* safe);

 public:
  bool			InitThread(void routine(SafeQueue* safe));
  bool			StartThread();
  bool			WaitThread();
  void			DestroyThread();
};

#endif
