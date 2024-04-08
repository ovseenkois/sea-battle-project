#include "../headers/symbol.h"

sf::Font Symbol::font_ = sf::Font();

void Symbol::MakeFont() {
  Symbol::font_.loadFromFile("../visual/arialmt.ttf");
}

Symbol::Symbol(std::string str) {
  text_.setFont(font_);
  text_.setString(str);
  text_.setCharacterSize(24);
  text_.setFillColor(sf::Color::Black);
}