#ifndef STATE_H
#define STATE_H
class PlayerState;
#include "player.h"

class PlayerState {
 public:
  virtual void Handle(sf::Event& event, sf::RenderWindow& window, Player& player, Player& other_player) = 0;
  virtual std::unique_ptr<PlayerState> Next() = 0;
  ~PlayerState() = default;
};

class PlacingShips : public PlayerState {
 public:
  void Handle(sf::Event& event, sf::RenderWindow& window, Player& player, Player& other_player) override;
  std::unique_ptr<PlayerState> Next() override;
};

class Waiting : public PlayerState {
 public:
  void Handle(sf::Event& event, sf::RenderWindow& window, Player& player, Player& other_player) override {
  }
  std::unique_ptr<PlayerState> Next() override;
};

class Attack : public PlayerState {
 public:
  void Handle(sf::Event& event, sf::RenderWindow& window, Player& player, Player& other_player) override;
  std::unique_ptr<PlayerState> Next() override;
};

class Starting : public PlayerState {
 public:
  void Handle(sf::Event& event, sf::RenderWindow& window, Player& player, Player& other_player) override {
  }
  std::unique_ptr<PlayerState> Next() override;
};

#endif