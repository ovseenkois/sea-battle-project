#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

struct Point {
  int x_;
  int y_;
};

class IShip {};

class Cell {
  sf::RectangleShape shape_;
  int size_;
  IShip* ptr_to_ship_;

 public:
  Cell() = default;
  Cell(sf::RectangleShape shape, int size, IShip* ptr) : shape_(shape), size_(size), ptr_to_ship_(ptr) {
  }
  sf::RectangleShape GetShape() {
    return shape_;
  }
};

class Board {
 private:
  int size_;
  Point begin_;
  int cell_size_;
  std::vector<std::vector<Cell>> board_;

 public:
  Board(int size, Point begin, int cell_size) : size_(size), begin_(begin), cell_size_(cell_size) {
    board_.reserve(size_);
    for (int i = 0; i < size_; ++i) {
      board_[i].reserve(size_);
    };
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        sf::RectangleShape shape(sf::Vector2f(cell_size_, cell_size_));
        sf::Color cell_color(180, 180, 255);
        shape.setOutlineColor(cell_color);
        shape.setOutlineThickness(cell_size_ / 20);
        shape.setPosition(begin_.x_ + i * cell_size_, begin_.y_ + j * cell_size_);
        Cell cell(shape, cell_size_, nullptr);
        board_[i][j] = cell;
      }
    }
  }
  void Draw(sf::RenderWindow& window) {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        window.draw(board_[i][j].GetShape());
      }
    }
  }
};
