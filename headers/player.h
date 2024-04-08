#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include "ship.h"
#include <memory>
class Player;
#include "playerstate.h"

enum Strikes { HIT, MISS, FALSE };

struct Aim  {
  void Move(sf::Event& event, Board& board) ;
  Strikes Set(sf::Event& event, Board& board) ;

  // bool CanStay(int i_, int j_, Board& board);
  // void SetBoundaries(int i_, int j_, Board& board);
};


class Player {
  friend PlayerState;
  Board& board_;
  std::vector<std::unique_ptr<IShip>> ships_;
  int counter_;
  std::unique_ptr<PlayerState> state_;
  Aim aim_;

 public:
  Player(Board& board, std::unique_ptr<PlayerState> state);
  ~Player();
  void MoveShip(sf::Event& event);
  void SetShip(sf::Event& event, Player& other_player);
  void RotateShip(sf::Event& event, sf::RenderWindow& window);
  void SetState(std::unique_ptr<PlayerState> state);
  void Handle(sf::Event& event, sf::RenderWindow& window, Player& other_player);
  void SendRequestToChangeState(Player& player, std::unique_ptr<PlayerState> state);
  void Choose(sf::Event& event, Player& other_player);
  void Strike(sf::Event& event, Player& other_player);
  void CheckShips();
};

#endif
