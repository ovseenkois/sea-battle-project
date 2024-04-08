#include "../headers/playerstate.h"

void PlacingShips::Handle(sf::Event& event, sf::RenderWindow& window, Player& player, Player& other_player) {
  if (event.type == sf::Event::KeyPressed) {
    player.RotateShip(event, window);
  }
  if (event.type == sf::Event::MouseMoved) {
    player.MoveShip(event);
  }
  if (event.type == sf::Event::MouseButtonPressed) {
    player.SetShip(event, other_player);
  }
}

void Attack::Handle(sf::Event& event, sf::RenderWindow& window, Player& player, Player& other_player) {
  if (event.type == sf::Event::MouseMoved) {
    player.Choose(event, other_player);
  }
  if (event.type == sf::Event::MouseButtonPressed) {
    player.Strike(event, other_player);
  }
}

std::unique_ptr<PlayerState> PlacingShips::Next() {
  return std::unique_ptr<PlayerState>(new Waiting());
}
std::unique_ptr<PlayerState> Attack::Next() {
  return std::unique_ptr<PlayerState>(new Waiting());
}
std::unique_ptr<PlayerState> Waiting::Next() {
  return std::unique_ptr<PlayerState>(new Attack());
}

std::unique_ptr<PlayerState> Starting::Next() {
  return std::unique_ptr<PlayerState>(new PlacingShips());
}