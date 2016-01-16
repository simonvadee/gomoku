#include "UThread.hh"

UThread::UThread(SafeQueue* safe)
  : _stock(safe)
{
}

UThread::~UThread()
{
  DestroyThread();
}

bool UThread::InitThread(void routine(SafeQueue* safe))
{
  _routine = routine;
  return true;
}

bool UThread::StartThread()
{
  _thread = new std::thread(_routine, _stock);
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
