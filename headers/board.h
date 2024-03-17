#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "point.h"
#include "cell.h"

class Board {
  friend class Ship1;
  friend class Ship2;
  friend class Ship3;
  friend class Ship4;

 private:
  int size_;
  Point begin_;
  int cell_size_;
  std::vector<std::vector<Cell>> board_;

 public:
  Board(int size, Point begin, int cell_size);
  void Draw(sf::RenderWindow& window);
};
#endif