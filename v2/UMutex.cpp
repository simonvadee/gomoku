# include "UMutex.hh"

UMutex::UMutex()
{
}

UMutex::~UMutex()
{
}

void UMutex::InitMutex()
{
}

void UMutex::DestroyMutex()
{
}

void UMutex::LockMutex()
{
  _mutex.lock();
}

bool UMutex::TrylockMutex()
{
  return _mutex.try_lock();
}

void UMutex::UnlockMutex()
{
  _mutex.unlock();
}
