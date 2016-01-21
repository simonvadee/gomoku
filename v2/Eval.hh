#ifndef EVAL_H_
# define EVAL_H_

# include <vector>
# include <string>
# include <iostream>
# include <fstream>
# include <exception>
# include <cstdlib>
# include "Player.hh"

class		Eval
{
  typedef enum
    {
      ALIGNEMENT,
      EAT,
      BLOCK,
      WIN
    }		scores;
private :
  std::vector<int>	_scores;
  char**		_map;

public :
  Eval(char**, std::string filename = "./data/IA_default.txt");
  ~Eval();
  int	megaval(Pos&, PLAYER);

private :
  int	_eval__alignment(Pos& pos, PLAYER player);
  int	_eval__eat(Pos& pos, PLAYER player);
  int	_eval__block(Pos& pos, PLAYER player);
  int	_eval__win(Pos& pos, PLAYER player);
};

class		FileExistException : public std::exception
{
private :
  std::string	_message;
public :
  virtual const char* what() const throw()
  {
    return _message.c_str();
  }
  virtual ~FileExistException() {}
  FileExistException(std::string const& msg)
    : _message(msg)
  {}
};

#endif /* !EVAL_H_ */
