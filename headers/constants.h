#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "cell.h"


class Constants {
 public:
  Cell BoardCell(sf::Vector2f coord);
  Cell ShipCell(IShip* ship, sf::Vector2f coord);
  Cell XCell(sf::Vector2f coord);
};
#endif