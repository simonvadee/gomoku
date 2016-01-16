#include "Eval.hh"

Eval::Eval(std::string filename)
{
  std::ifstream	file;

  file.exceptions(std::ifstream::eofbit);

  try {
    file.open(filename.c_str(), std::ifstream::in);
    if (!file)
      throw FileExistException("File " + filename + " does not exist, Init Eval failed");

    std::string scoreDef;
    while (!file.eof())
      {
	std::getline(file, scoreDef);
	_scores.push_back(std::atoi(scoreDef.substr(scoreDef.size() - 1).c_str()));
      }
  }
  catch (std::ifstream::failure e) {
    for (auto &it : _scores)
      std::cout << it << std::endl;
  }
  file.close();
}

Eval::~Eval()
{}

int		Eval::megaval(Pos& pos, PLAYER player)
{
  return (_eval__alignment(pos, player)
	  + _eval__eat(pos, player)
	  + _eval__block(pos, player)
	  + _eval__win(pos, player));
}

int		Eval::_eval__alignment(Pos&, PLAYER)
{
  return 0;
}

int		Eval::_eval__eat(Pos&, PLAYER)
{
  return 0;
}

int		Eval::_eval__block(Pos&, PLAYER)
{
  return 0;
}

int		Eval::_eval__win(Pos&, PLAYER)
{
  return 0;
}
