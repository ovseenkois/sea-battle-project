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
  IShip* GetPtr() {
    return ptr_to_ship_;
  }
  void SetAvailable(bool x) {
    available_to_set_ = x;
  }
};

class Board {
  friend class Ship1;
  friend class Ship2;

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
        shape.setPosition(begin_.x_ + i * (cell_size_ + 100 / 20), begin_.y_ + j * (cell_size_ + 100 / 20));
        Cell cell(shape, cell_size_, nullptr);
        board_[j][i] = cell;
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
    new_cell.SetAvailable(false);
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
      if (j - 1 >= 0 && arr.board_[i][j - 1].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i][j - 1].GetCoordinates());
        arr.board_[i][j - 1] = new_cell;
        arr.board_[i][j] = old_cell;
        begin_ = Point(j - 1, i);
      }
    }
    if (event.key.code == sf::Keyboard::Right) {
      if (j + 1 < arr.size_ && arr.board_[i][j + 1].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i][j + 1].GetCoordinates());
        arr.board_[i][j + 1] = new_cell;
        arr.board_[i][j] = old_cell;
        begin_ = Point(j + 1, i);
      }
    }
    if (event.key.code == sf::Keyboard::Up) {
      if (i - 1 >= 0 && arr.board_[i - 1][j].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i - 1][j].GetCoordinates());
        arr.board_[i - 1][j] = new_cell;
        arr.board_[i][j] = old_cell;
        begin_ = Point(j, i - 1);
      }
    }
    if (event.key.code == sf::Keyboard::Down) {
      if (i + 1 < arr.size_ && arr.board_[i + 1][j].IsAvailableToSet()) {
        auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
        auto new_cell = Constants().ShipCell(this, arr.board_[i + 1][j].GetCoordinates());
        arr.board_[i + 1][j] = new_cell;
        arr.board_[i][j] = old_cell;
        begin_ = Point(j, i + 1);
      }
    }
  }
};

enum Orientation { LEFT, RIGHT, UP, DOWN };

class Ship2 : public IShip {
  Point begin_;
  int size_ = 2;
  bool dead = false;
  Orientation orientation = RIGHT;

 public:
  Ship2() = default;
  Ship2(Point begin) : begin_(begin) {
  }
  void Move(sf::Event& event, Board& arr) override {
    int i = begin_.y_;
    int j = begin_.x_;
    auto orient = orientation;
    if (orient == RIGHT) {
      if (event.key.code == sf::Keyboard::R) {
        if (i - 1 >= 0 && arr.board_[i - 1][j].IsAvailableToSet()) {
          auto old_cell = Constants().BoardCell(arr.board_[i][j + 1].GetCoordinates());
          auto new_cell = Constants().ShipCell(this, arr.board_[i - 1][j].GetCoordinates());
          arr.board_[i - 1][j] = new_cell;
          arr.board_[i][j + 1] = old_cell;
          orientation = UP;
        }
      }
      if (event.key.code == sf::Keyboard::Left) {
        if (j - 1 >= 0 && arr.board_[i][j - 1].IsAvailableToSet()) {
          auto old_cell = Constants().BoardCell(arr.board_[i][j + 1].GetCoordinates());
          auto new_cell = Constants().ShipCell(this, arr.board_[i][j - 1].GetCoordinates());
          arr.board_[i][j - 1] = new_cell;
          arr.board_[i][j + 1] = old_cell;
          begin_ = Point(j - 1, i);
        }
      }
      if (event.key.code == sf::Keyboard::Right) {
        if (j + 2 < arr.size_ && arr.board_[i][j + 2].IsAvailableToSet()) {
          auto old_cell = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
          auto new_cell = Constants().ShipCell(this, arr.board_[i][j + 2].GetCoordinates());
          arr.board_[i][j + 2] = new_cell;
          arr.board_[i][j] = old_cell;
          begin_ = Point(j + 1, i);
        }
      }
      if (event.key.code == sf::Keyboard::Up) {
        if (i - 1 >= 0 && arr.board_[i - 1][j].IsAvailableToSet() && arr.board_[i - 1][j + 1].IsAvailableToSet()) {
          auto old_cell1 = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
          auto old_cell2 = Constants().BoardCell(arr.board_[i][j + 1].GetCoordinates());
          auto new_cell1 = Constants().ShipCell(this, arr.board_[i - 1][j].GetCoordinates());
          auto new_cell2 = Constants().ShipCell(this, arr.board_[i - 1][j + 1].GetCoordinates());
          arr.board_[i - 1][j] = new_cell1;
          arr.board_[i - 1][j + 1] = new_cell2;
          arr.board_[i][j] = old_cell1;
          arr.board_[i][j + 1] = old_cell2;
          begin_ = Point(j, i - 1);
        }
      }
      if (event.key.code == sf::Keyboard::Down) {
        if (i + 1 < arr.size_ && arr.board_[i + 1][j].IsAvailableToSet() &&
            arr.board_[i + 1][j + 1].IsAvailableToSet()) {
          auto old_cell1 = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
          auto old_cell2 = Constants().BoardCell(arr.board_[i][j + 1].GetCoordinates());
          auto new_cell1 = Constants().ShipCell(this, arr.board_[i + 1][j].GetCoordinates());
          auto new_cell2 = Constants().ShipCell(this, arr.board_[i + 1][j + 1].GetCoordinates());
          arr.board_[i + 1][j] = new_cell1;
          arr.board_[i + 1][j + 1] = new_cell2;
          arr.board_[i][j] = old_cell1;
          arr.board_[i][j + 1] = old_cell2;
          begin_ = Point(j, i + 1);
        }
      }
    }
    if (orient == UP) {
      if (event.key.code == sf::Keyboard::R) {
        if (j + 1 < arr.size_ && arr.board_[i][j + 1].IsAvailableToSet()) {
          auto old_cell = Constants().BoardCell(arr.board_[i - 1][j].GetCoordinates());
          auto new_cell = Constants().ShipCell(this, arr.board_[i][j + 1].GetCoordinates());
          arr.board_[i - 1][j] = old_cell;
          arr.board_[i][j + 1] = new_cell;
          orientation = RIGHT;
        }
      }
      if (event.key.code == sf::Keyboard::Left) {
        if (j - 1 >= 0 && arr.board_[i][j - 1].IsAvailableToSet() && arr.board_[i - 1][j - 1].IsAvailableToSet()) {
          auto old_cell1 = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
          auto old_cell2 = Constants().BoardCell(arr.board_[i - 1][j].GetCoordinates());

          auto new_cell1 = Constants().ShipCell(this, arr.board_[i][j - 1].GetCoordinates());
          auto new_cell2 = Constants().ShipCell(this, arr.board_[i - 1][j - 1].GetCoordinates());

          arr.board_[i][j] = old_cell1;
          arr.board_[i - 1][j] = old_cell2;
          arr.board_[i][j - 1] = new_cell1;
          arr.board_[i - 1][j - 1] = new_cell2;
          begin_ = Point(j - 1, i);
        }
      }
      if (event.key.code == sf::Keyboard::Right) {
        if (j + 1 < arr.size_ && arr.board_[i][j + 1].IsAvailableToSet() &&
            arr.board_[i - 1][j + 1].IsAvailableToSet()) {
          auto old_cell1 = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
          auto old_cell2 = Constants().BoardCell(arr.board_[i - 1][j].GetCoordinates());

          auto new_cell1 = Constants().ShipCell(this, arr.board_[i][j + 1].GetCoordinates());
          auto new_cell2 = Constants().ShipCell(this, arr.board_[i - 1][j + 1].GetCoordinates());

          arr.board_[i][j] = old_cell1;
          arr.board_[i - 1][j] = old_cell2;
          arr.board_[i][j + 1] = new_cell1;
          arr.board_[i - 1][j + 1] = new_cell2;
          begin_ = Point(j + 1, i);
        }
      }
      if (event.key.code == sf::Keyboard::Up) {
        if (i - 2 >= 0 && arr.board_[i - 2][j].IsAvailableToSet()) {
          auto old_cell1 = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
          auto old_cell2 = Constants().BoardCell(arr.board_[i - 1][j].GetCoordinates());

          auto new_cell1 = Constants().ShipCell(this, arr.board_[i - 1][j].GetCoordinates());
          auto new_cell2 = Constants().ShipCell(this, arr.board_[i - 2][j].GetCoordinates());

          arr.board_[i][j] = old_cell1;
          arr.board_[i - 1][j] = old_cell2;
          arr.board_[i - 1][j] = new_cell1;
          arr.board_[i - 2][j] = new_cell2;
          begin_ = Point(j, i - 1);
        }
      }
      if (event.key.code == sf::Keyboard::Down) {
        if (i + 1 < arr.size_ && arr.board_[i + 1][j].IsAvailableToSet()) {
          auto old_cell1 = Constants().BoardCell(arr.board_[i][j].GetCoordinates());
          auto old_cell2 = Constants().BoardCell(arr.board_[i - 1][j].GetCoordinates());

          auto new_cell1 = Constants().ShipCell(this, arr.board_[i + 1][j].GetCoordinates());
          auto new_cell2 = Constants().ShipCell(this, arr.board_[i][j].GetCoordinates());

          arr.board_[i][j] = old_cell1;
          arr.board_[i - 1][j] = old_cell2;
          arr.board_[i + 1][j] = new_cell1;
          arr.board_[i][j] = new_cell2;
          begin_ = Point(j, i + 1);
        }
      }
    }
  }
};
