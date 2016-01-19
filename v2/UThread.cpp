#include "UThread.hh"

UThread::UThread(SafeQueue* safe, unsigned int mapSize)
  : _stock(safe), _mapSize(mapSize)
{
}

UThread::~UThread()
{
  DestroyThread();
}

bool UThread::InitThread(void routine(SafeQueue* safe, unsigned int mapSize))
{
  _routine = routine;
  return true;
}

bool UThread::StartThread()
{
  _thread = new std::thread(_routine, _stock, _mapSize);
  return true;
}

bool UThread::WaitThread()
{
  _thread->join();
  return true;
}

void UThread::DestroyThread()
{
  delete _thread;
}
