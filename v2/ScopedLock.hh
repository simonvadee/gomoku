#ifndef SCOPEDLOCK_HH_
# define SCOPEDLOCK_HH_

# include "UMutex.hh"

class			ScopedLock
{
public:
  ScopedLock(UMutex* mutex);
  ~ScopedLock();

private:
  UMutex*		_mutex;
};

#endif
