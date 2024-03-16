#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Cell {
  sf::RectangleShape shape_;
  int size_;
  IShip* ptr_to_ship_;
  bool available_to_set_ = true;

 public:
  Cell() = default;
  Cell(sf::RectangleShape shape, int size, IShip* ptr)
      : shape_(shape), size_(size), ptr_to_ship_(ptr), available_to_set_(true) {
  }
  sf::RectangleShape GetShape() {
    return shape_;
  }
  bool IsAvailableToSet() {
    return available_to_set_;
  }
};