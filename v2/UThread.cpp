#include "UThread.hh"

UThread::UThread(SafeQueue* safe, unsigned int mapSize, char **map)
  : _stock(safe), _mapSize(mapSize), _map(map)
{
}

UThread::~UThread()
{
  DestroyThread();
}

bool UThread::InitThread(void routine(SafeQueue* safe, unsigned int mapSize, char **map))
{
  _routine = routine;
  return true;
}

bool UThread::StartThread()
{
  _thread = new std::thread(_routine, _stock, _mapSize, _map);
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
