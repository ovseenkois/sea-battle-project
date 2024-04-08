#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "cell.h"

class Constants {
 public:
  static sf::Texture x;
  static void MakeX() {
    x.loadFromFile("../visual/x.png");
  }
  static sf::Texture point;
  static void MakePoint() {
    point.loadFromFile("../visual/point.png");
  }
  static const int board_size = 10;
  static const int cell_size = 50;
  static Cell BoardCell(sf::Vector2f coord);
  static Cell ShipCell(IShip* ship, sf::Vector2f coord);
  static Cell XCell(sf::Vector2f coord);
  static Cell ChooseCell(sf::Vector2f coord);
  static Cell HitCell(sf::Vector2f coord);
  static Cell MissCell(sf::Vector2f coord);
  // static Cell NotAvailableCell(IShip* ship, sf::Vector2f coord);
  static Cell HideBoardCell(Cell boardcell);
  // static Cell ShowBoardCell(Cell boardcell);
};
#endif