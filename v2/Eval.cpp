#include "Eval.hh"

extern Pos _dir[4];

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
  // 1 : win -> 5 aligné ou 10 de score
  // 2 : bloquer alignement 5 de l'adversaire ou empecher de manger si score adverse == 8
  // 3 : faire un 4 libre
  // 4 : empecher 4 libre
  // 4 : bloquer un 3 libre
  // 5 : manger deux pièces
  // 6 : empêcher l'autre de manger
  // 7 : poids des aligements
  return (_eval__alignment(map, pos, player, false)
	  + (_eval__alignment(map, pos, static_cast<PLAYER>(OPPONENT(player)), true))
	  + _eval__eat(map, pos, player)
	  + _eval__block(map, pos, player)
	  + _eval__win(map, pos, player));
}

int		Eval::_eval__alignment(char **map, Pos& pos, PLAYER player, bool counter)
{
  int		weightHor = Board::getAlignement(map, pos, _dir[HORIZONTAL], player, false);
  int		weightVer = Board::getAlignement(map, pos, _dir[VERTICAL], player, false);
  int		weightDLR = Board::getAlignement(map, pos, _dir[DIAGONAL_LR], player, false);
  int		weightDRL = Board::getAlignement(map, pos, _dir[DIAGONAL_RL], player, false);

  if (weightVer >= 5
      || weightHor >= 5
      || weightDRL >= 5
      || weightDLR >= 5)
    return 100;
  else if (weightVer >= 4
      || weightHor >= 4
      || weightDRL >= 4
      || weightDLR >= 4)
    return 75;
  return weightHor + weightVer + weightDLR + weightDRL;
}

int		Eval::_eval__eat(char **map, Pos& pos, PLAYER player)
{
  Pos		del1;
  Pos		del2;
  Pos		allied;


  for (unsigned int i = 0; i < 4; ++i)
    {
      del1.x = pos.x + _dir[i].x;
      del1.y = pos.y + _dir[i].y;
      del2.x = pos.x + (_dir[i].x * 2);
      del2.y = pos.y + (_dir[i].y * 2);
      allied.x = pos.x + (_dir[i].x * 3);
      allied.y = pos.y + (_dir[i].y * 3);
      if (Board::canEatPieces(map, del1, del2, allied, player))
	return 50;
      del1.x = pos.x - _dir[i].x;
      del1.y = pos.y - _dir[i].y;
      del2.x = pos.x - (_dir[i].x * 2);
      del2.y = pos.y - (_dir[i].y * 2);
      allied.x = pos.x - (_dir[i].x * 3);
      allied.y = pos.y - (_dir[i].y * 3);
      if (Board::canEatPieces(map, del1, del2, allied, player))
	return 50;
    }
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
