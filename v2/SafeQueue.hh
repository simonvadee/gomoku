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
  bool						_gameRunning;
  UMutex*					_gameRunningMutex;
  UMutex*					_stockMutex;
  UMutex*					_processedMutex;
  
public:
  std::vector<std::pair<char**, Pos>*>*		_stock; ////
  std::vector<std::pair<int, Pos>*>*		_processed;


  std::pair<char**, Pos>*			popStock();
  std::pair<int, Pos>*				popProcessed();
  void						fillStock(std::pair<char**, Pos>* map);
  void						fillProcessed(std::pair<int, Pos>* res);
  bool						isGameRunning();
  void						setGameRunning(bool value);
};

#endif
