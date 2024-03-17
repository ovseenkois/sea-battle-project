#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "board.h"

enum Orientation { RIGHT, DOWN };

class IShip {
 public:
  virtual void Move(sf::Event&, Board&) = 0;
  virtual ~IShip() = default;
  virtual void Rotate(sf::Event&, Board&, sf::RenderWindow&) = 0;
  virtual void Set(sf::Event&, Board&) = 0;
};

class Ship1 : public IShip {
  Point begin_;
  int size_ = 1;
  bool dead = false;
  // Cell* part1;

 public:
  Ship1() = default;
  Ship1(Point begin) : begin_(begin) {
  }
  void Move(sf::Event& event, Board& board) override;
  void Set(sf::Event& event, Board& board) override;
  void Rotate(sf::Event&, Board&, sf::RenderWindow&) override {
  }

  // void Rotate(sf::Event& event, Board& arr) override {
  // }
};

class Ship2 : public IShip {
  Point begin_;
  int size_ = 2;
  bool dead_ = false;
  Orientation orientation_ = RIGHT;
  // Cell* part1;
  // Cell* part2;

 public:
  Ship2() = default;
  Ship2(Point begin) : begin_(begin) {
  }
  void Move(sf::Event& event, Board& board) override;
  void Set(sf::Event& event, Board& board) override;
  void Rotate(sf::Event& event, Board& board, sf::RenderWindow& window) override;
};

class Ship3 : public IShip {
  Point begin_;
  int size_ = 3;
  bool dead_ = false;
  Orientation orientation_ = RIGHT;

 public:
  Ship3() = default;
  Ship3(Point begin) : begin_(begin) {
  }
  void Move(sf::Event& event, Board& board) override;
  void Set(sf::Event& event, Board& board) override;
  void Rotate(sf::Event&, Board&, sf::RenderWindow&) override {
  }
};

class Ship4 : public IShip {
  Point begin_;
  int size_ = 4;
  bool dead_ = false;
  Orientation orientation_ = RIGHT;

 public:
  Ship4() = default;
  Ship4(Point begin) : begin_(begin) {
  }
  void Move(sf::Event& event, Board& board) override;
  void Set(sf::Event& event, Board& board) override;
  void Rotate(sf::Event&, Board&, sf::RenderWindow&) override {
  }
};

#endif
