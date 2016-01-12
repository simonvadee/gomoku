#ifndef PLAYER_H_
# define PLAYER_H_

typedef enum
  {
    PLAYER1 = 1,
    PLAYER2
  } PLAYER;

class Player
{
public:

  ~Player() {};

  virtual bool		play() = 0;

 private:

  // gui

};

#endif /* !PLAYER_H_ */
