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

public :
  Eval(std::string filename = "./data/IA_default.txt");
  ~Eval();
  int	megaval(char **map, Pos&, PLAYER);

private :
  int	_eval__alignment(char **map, Pos& pos, PLAYER player);
  int	_eval__eat(char **map, Pos& pos, PLAYER player);
  int	_eval__block(char **map, Pos& pos, PLAYER player);
  int	_eval__win(char **map, Pos& pos, PLAYER player);
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
