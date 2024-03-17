#include "headers/constants.h"
#include <memory>

struct XTexture {

};


Cell Constants::BoardCell(sf::Vector2f coord) {
  sf::RectangleShape shape(sf::Vector2f(50, 50));
  sf::Color cell_color(180, 180, 255);
  shape.setOutlineColor(cell_color);
  shape.setOutlineThickness(50 / 20);  
  shape.setPosition(coord);
  Cell cell(shape, 50, nullptr);
  return cell;
}
Cell Constants::ShipCell(IShip* ship, sf::Vector2f coord) {
  sf::RectangleShape new_shape(sf::Vector2f(50, 50));
  sf::Color col(0, 0, 255);
  new_shape.setOutlineColor(col);
  new_shape.setOutlineThickness(50 / 20);
  new_shape.setPosition(coord);
  Cell new_cell(new_shape, 50, ship);
  new_cell.SetAvailable(false);
  return new_cell;
}
Cell Constants::XCell(sf::Vector2f coord) {
  sf::RectangleShape shape(sf::Vector2f(50, 50));
  sf::Color cell_color(255, 0, 0);
  shape.setOutlineColor(cell_color);
  shape.setOutlineThickness(50 / 20);  
  shape.setPosition(coord);
  Cell cell(shape, 50, nullptr);
  return cell;
}