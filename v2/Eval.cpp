#include "Eval.hh"

Eval::Eval(std::string filename)
{
  // std::ifstream	file;

  // file.exceptions(std::ifstream::eofbit);

  // try {
  //   file.open(filename.c_str(), std::ifstream::in);
  //   if (!file)
  //     throw FileExistException("File " + filename + " does not exist, Init Eval failed");

  //   std::string scoreDef;
  //   while (!file.eof())
  //     {
  // 	std::getline(file, scoreDef);
  // 	_scores.push_back(std::atoi(scoreDef.substr(scoreDef.size() - 1).c_str()));
  //     }
  // }
  // catch (std::ifstream::failure e) {
  //   for (auto &it : _scores)
  //     std::cout << it << std::endl;
  // }
  // file.close();
}

Eval::~Eval()
{}

int		Eval::megaval(char **map, Pos& pos, PLAYER player)
{
  return (_eval__alignment(map, pos, player)
	  + _eval__eat(map, pos, player)
	  + _eval__block(map, pos, player)
	  + _eval__win(map, pos, player));
}

int		Eval::_eval__alignment(char **map, Pos& pos, PLAYER player)
{
  return 0;
}

int		Eval::_eval__eat(char **map, Pos& pos, PLAYER player)
{
  return 0;
}

int		Eval::_eval__block(char **map, Pos& pos, PLAYER player)
{
  return 0;
}

int		Eval::_eval__win(char **map, Pos& pos, PLAYER player)
{
  return 0;
}
