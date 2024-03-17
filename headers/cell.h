#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class IShip;

class Cell {
  sf::RectangleShape shape_;
  int size_;
  IShip* ptr_to_ship_;
  bool available_to_set_ = true;

 public:
  Cell();
  Cell(sf::RectangleShape shape, int size, IShip* ptr);
  sf::RectangleShape GetShape();
  bool IsAvailableToSet();
  sf::Vector2f GetCoordinates();
  IShip* GetPtr();
  void SetAvailable(bool x);
};
#endif