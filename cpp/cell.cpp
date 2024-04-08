#include "../headers/cell.h"

Cell::Cell() = default;

Cell::Cell(sf::RectangleShape shape, int size, IShip* ptr)
    : shape_(shape), size_(size), ptr_to_ship_(ptr), available_to_set_(true) {
}

sf::RectangleShape Cell::GetShape() {
  return shape_;
}

bool Cell::IsAvailableToSet() {
  return available_to_set_;
}

sf::Vector2f Cell::GetCoordinates() {
  return shape_.getPosition();
}

IShip* Cell::GetPtr() {
  return ptr_to_ship_;
}

void Cell::SetAvailable(bool x) {
  available_to_set_ = x;
}

void Cell::SetPtr(IShip* ptr) {
  ptr_to_ship_ = ptr;
}

void Cell::SetOutlineColor(sf::Color color) {
  shape_.setOutlineColor(color);
}

void Cell::SetTemporary(bool x) {
  temporary_ = x;
}

bool Cell::GetTemporary() {
  return temporary_;
}
 
void Cell::Destroy() {
  destroyed_ = true;
}

bool Cell::IsDestroyed() {
  return destroyed_;
}