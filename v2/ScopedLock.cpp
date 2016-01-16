#include "ScopedLock.hh"

ScopedLock::ScopedLock(UMutex* mutex)
  : _mutex(mutex)
{
  _mutex->LockMutex();
}

ScopedLock::~ScopedLock()
{
  _mutex->UnlockMutex();
}
