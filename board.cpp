#include "headers/board.h"

Board::Board(int size, Point begin, int cell_size) : size_(size), begin_(begin), cell_size_(cell_size) {
  board_.resize(size_);
  for (int i = 0; i < size_; ++i) {
    board_[i].resize(size_);
  };
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      sf::RectangleShape shape(sf::Vector2f(cell_size_, cell_size_));
      sf::Color cell_color(180, 180, 255);
      shape.setOutlineColor(cell_color);
      shape.setOutlineThickness(cell_size_ / 20);
      shape.setPosition(begin_.x_ + i * (cell_size_ + 100 / 20), begin_.y_ + j * (cell_size_ + 100 / 20));
      Cell cell(shape, cell_size_, nullptr);
      board_[j][i] = cell;
    }
  }
}
void Board::Draw(sf::RenderWindow& window) {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      window.draw(board_[i][j].GetShape());
    }
  }
}