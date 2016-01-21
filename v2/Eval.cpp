#include "Eval.hh"

extern Pos _dir[4];

Eval::Eval(char** map, std::string filename)
  : _map(map)
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

int		Eval::_eval__alignment(Pos& pos, PLAYER player)
{
  int size = 0;

  size += Board::getAlignement(_map, pos, _dir[HORIZONTAL], player, false) - 1;
  size += Board::getAlignement(_map, pos, _dir[VERTICAL], player, false) - 1;
  size += Board::getAlignement(_map, pos, _dir[DIAGONAL_LR], player, false) - 1;
  size += Board::getAlignement(_map, pos, _dir[DIAGONAL_RL], player, false) - 1;

  return (size * _scores[ALIGNEMENT]);
}

int		Eval::_eval__eat(Pos& pos, PLAYER player)
{
  Pos del1;
  Pos del2;
  Pos allied;

  int size = 0;

  for (int i = 0; i < 4; i++)
    {
      del1.x = pos.x + _dir[i].x * 1;
      del1.y = pos.y + _dir[i].y * 1;;
      del2.x = pos.x + _dir[i].x * 2;
      del2.y = pos.y + _dir[i].y * 2;;
      allied.x = pos.x + _dir[i].x * 3;
      allied.y = pos.y + _dir[i].y * 3;;
      size += Board::canEatPieces(_map, del1, del2, allied, player);
    }
 return (size * _scores[EAT]);
}

int		Eval::_eval__block(Pos&, PLAYER)
{
  return 0;
}

int		Eval::_eval__win(Pos& pos, PLAYER player)
{

  return 0;
}
