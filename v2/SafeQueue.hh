#ifndef SAFEQUEUE_HH_
# define SAFEQUEUE_HH_

# include <vector>
# include <string>
# include "Board.hh"
# include "ScopedLock.hh"

class SafeQueue
{
public:
  SafeQueue();
  virtual ~SafeQueue();
  
private:
  UMutex*					_stockMutex;
  UMutex*					_processedMutex;
  bool						_gameRunning;
  UMutex*					_gameRunningMutex;
  
public:
  std::vector<std::vector<Pos>*>*		_stock; // MUST BE PRIVATE
  std::vector<std::pair<int, Pos>*>*		_processed;

  bool						isGameRunning();
  void						setGameRunning(bool value);
  std::vector<Pos>*				popStock();
  std::pair<int, Pos>*				popProcessed();
  void						fillStock(std::pair<char**, Pos>* map);
  void						fillProcessed(std::pair<int, Pos>* res);
};

#endif
