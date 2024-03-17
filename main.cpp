#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "headers/board.h"
#include "headers/ship.h"

int main() {
  std::vector<IShip*> ships;
  ships.reserve(10);
  int index = 0;
  for (int i = 0; i < 10; ++i) {
    if (i <= 3) {
      ships.push_back(new Ship1());
    }
    if (i >= 4 && i <= 6) {
      ships.push_back(new Ship2());
    }
    if (i >= 7 && i <= 8) {
      ships.push_back(new Ship3());
    }
    if (i == 9) {
      ships.push_back(new Ship4());
    }
  }
  sf::RenderWindow window(sf::VideoMode(1600, 800), "Naval Battle");
  window.setKeyRepeatEnabled(false);

  Board board(10, Point(100, 100), 50);  // поле

  sf::RectangleShape game_background;  // задний фон
  game_background.setFillColor(sf::Color(255, 255, 255));
  game_background.setSize(sf::Vector2f(1600, 800));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      }
      if (index < 10) {
        if (event.type == sf::Event::KeyPressed) {
          ships[index]->Rotate(event, board, window);
        }
        if (event.type == sf::Event::MouseMoved) {
          ships[index]->Move(event, board);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
          ships[index]->Set(event, board);
          ++index;
        }
      }
    }
    window.clear();

    window.draw(game_background);
    board.Draw(window);

    window.display();
  }
  for (auto i : ships) {
    delete i;
  }
}
