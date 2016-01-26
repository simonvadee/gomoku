#ifndef UMUTEX_H_
# define UMUTEX_H_

# include <mutex>

class				UMutex
{
public:
  UMutex();
  ~UMutex();

 private:
  std::mutex			_mutex;

 public:
  void				InitMutex();
  void				DestroyMutex();
  void				LockMutex();
  bool				TrylockMutex();
  void				UnlockMutex();
};

#endif
