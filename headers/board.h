#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

class IShip;

struct Point {
  int x_;
  int y_;
  Point() = default;
  Point(int x, int y) : x_(x), y_(y) {
  }
};

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
  sf::Vector2f GetCoordinates() {
    return shape_.getPosition();
  }
};

class Board {
  friend class Ship1;

 private:
  int size_;
  Point begin_;
  int cell_size_;
  std::vector<std::vector<Cell>> board_;

 public:
  Board(int size, Point begin, int cell_size) : size_(size), begin_(begin), cell_size_(cell_size) {
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

class IShip {
 public:
  virtual void Move(sf::Event&, Board&) = 0;
  virtual ~IShip() = default;
};

class Constants {
 public:
  Cell BoardCell(sf::Vector2f coord) {
    sf::RectangleShape shape(sf::Vector2f(50, 50));
    sf::Color cell_color(180, 180, 255);
    shape.setOutlineColor(cell_color);
    shape.setOutlineThickness(50 / 20);  // не определены координаты
    shape.setPosition(coord);
    Cell cell(shape, 50, nullptr);
    return cell;
  }
  Cell ShipCell(IShip* ship, sf::Vector2f coord) {
    sf::RectangleShape new_shape(sf::Vector2f(50, 50));
    sf::Color col(0, 0, 255);
    new_shape.setOutlineColor(col);
    new_shape.setOutlineThickness(50 / 20);
    new_shape.setPosition(coord);
    Cell new_cell(new_shape, 50, ship);
    return new_cell;
  }
};

class Ship1 : public IShip {
  Point begin_;
  int size_ = 1;
  bool dead = false;

 public:
  Ship1() = default;
  Ship1(Point begin) : begin_(begin) {
  }
  void Move(sf::Event& event, Board& arr) override {
    int i = begin_.y_;
    int j = begin_.x_;
    if (event.key.code == sf::Keyboard::Left) {
      if (arr.board_[i][j - 1].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i][j - 1].GetCoordinates());
        arr.board_[i][j - 1] = new_cell;
        arr.board_[i][j] = old_cell;
      }
      begin_ = Point(j - 1, i);
    }
    if (event.key.code == sf::Keyboard::Right) {
      if (arr.board_[i][j + 1].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i][j + 1].GetCoordinates());
        arr.board_[i][j + 1] = new_cell;
        arr.board_[i][j] = old_cell;
      }
      begin_ = Point(j + 1, i);
    }
    if (event.key.code == sf::Keyboard::Up) {
      if (arr.board_[i - 1][j].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i - 1][j].GetCoordinates());
        arr.board_[i - 1][j] = new_cell;
        arr.board_[i][j] = old_cell;
      }
      begin_ = Point(j, i - 1);
    }
    if (event.key.code == sf::Keyboard::Down) {
      if (arr.board_[i + 1][j].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i + 1][j].GetCoordinates());
        arr.board_[i + 1][j] = new_cell;
        arr.board_[i][j] = old_cell;
      }
      begin_ = Point(j, i + 1);
    }
  }
};
