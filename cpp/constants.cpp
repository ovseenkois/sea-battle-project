#include "../headers/constants.h"
#include <memory>

struct XTexture {};

sf::Texture Constants::x = sf::Texture();
sf::Texture Constants::point = sf::Texture();

Cell Constants::BoardCell(sf::Vector2f coord) {
  sf::RectangleShape shape(sf::Vector2f(50, 50));
  sf::Color cell_color(180, 180, 255);
  shape.setOutlineColor(cell_color);
  shape.setOutlineThickness(50 / 20);
  shape.setPosition(coord);
  Cell cell(shape, 50, nullptr);
  cell.SetAvailable(true);
  return cell;
}
Cell Constants::ShipCell(IShip* ship, sf::Vector2f coord) {
  sf::RectangleShape new_shape(sf::Vector2f(50, 50));
  sf::Color col(0, 0, 255);
  new_shape.setOutlineColor(col);
  new_shape.setOutlineThickness(50 / 20);
  new_shape.setPosition(coord);
  Cell new_cell(new_shape, 50, ship);
  if (ship) {
    new_cell.SetAvailable(false);
    new_cell.SetTemporary(false);
  } else {
    new_cell.SetAvailable(true);
    new_cell.SetTemporary(true);
  }
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
// Cell Constants::NotAvailableCell(IShip* ship, sf::Vector2f coord) {
//   sf::RectangleShape new_shape(sf::Vector2f(50, 50));
//   sf::Color col(180, 180, 255);
//   new_shape.setOutlineColor(col);
//   new_shape.setOutlineThickness(50 / 20);
//   new_shape.setPosition(coord);
//   Cell new_cell(new_shape, 50, ship);
//   new_cell.SetAvailable(false);
//   return new_cell;
// }

Cell Constants::HideBoardCell(Cell boardcell) {
  boardcell.SetOutlineColor({180, 180, 255});
  boardcell.SetTemporary(true);
  return boardcell;
}

// Cell Constants::ShowBoardCell(Cell boardcell) {
//   boardcell.SetOutlineColor({0, 0, 255});
//   return boardcell;

// }

Cell Constants::ChooseCell(sf::Vector2f coord) {
  sf::RectangleShape shape(sf::Vector2f(50, 50));
  sf::Color cell_color(221, 49, 255);
  shape.setOutlineColor(cell_color);
  shape.setOutlineThickness(50 / 20);
  shape.setPosition(coord);
  Cell cell(shape, 50, nullptr);
  cell.SetAvailable(true);
  return cell;
}

Cell Constants::HitCell(sf::Vector2f coord) {
  sf::RectangleShape shape(sf::Vector2f(50, 50));
  sf::Color cell_color(255, 0, 0);
  // MakeX();
  shape.setTexture(&x);
  shape.setOutlineColor(cell_color);
  shape.setOutlineThickness(50 / 20);
  shape.setPosition(coord);
  Cell cell(shape, 50, nullptr);
  cell.SetAvailable(true);
  cell.SetTemporary(false);
  return cell;
}

Cell Constants::MissCell(sf::Vector2f coord) {
  sf::RectangleShape shape(sf::Vector2f(50, 50));
  sf::Color cell_color(180, 180, 255);
  // MakePoint();
  shape.setTexture(&point);
  shape.setOutlineColor(cell_color);
  shape.setOutlineThickness(50 / 20);
  shape.setPosition(coord);
  Cell cell(shape, 50, nullptr);
  cell.SetAvailable(true);
  cell.SetTemporary(false);
  return cell;
}
