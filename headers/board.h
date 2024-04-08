#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "point.h"
#include "cell.h"
#include "constants.h"
#include "symbol.h"

class Board {
  friend class Ship1;
  friend class Ship2;
  friend class Ship3;
  friend class Ship4;
  friend class Aim;
  friend std::pair<int, int> CursorCoordinatesMove(sf::Event& event, Board& board);
  friend std::pair<int, int> CursorCoordinatesSet(sf::Event& event, Board& board);
  friend std::pair<int, int> CursorCoordinatesRotate(sf::Event& event, Board& board, sf::RenderWindow& window);

 private:
  int size_;
  Point begin_;
  int cell_size_;
  std::vector<std::vector<Cell>> close_board_;
  std::vector<std::vector<Cell>> open_board_;
  std::vector<Symbol> symbols_;

  bool open_ = true;

 public:
  Board(int size, Point begin, int cell_size);
  void Draw(sf::RenderWindow& window);
  void Clear();
  void Close();
  void Open();
  void CopyCloseToOpen();
};
#endif