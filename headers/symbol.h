#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Symbol {
  static sf::Font font_;

 public:
  static void MakeFont();
  sf::Text text_;
  std::string symbol_;
  Symbol() = default;
  Symbol(std::string str);
};

#endif