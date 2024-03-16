#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "headers/board.h"

int main() {
  IShip* ship1 = new Ship1(Point(1, 1));
  sf::RenderWindow window(sf::VideoMode(1600, 800), "My window");
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
      ship1->Move(event, board);
    }
    window.clear();

    window.draw(game_background);
    board.Draw(window);

    window.display();
  }
  delete static_cast<Ship1*>(ship1);
}

// else if (event.type == sf::Event::KeyPressed) {
//   if (event.key.code == sf::Keyboard::Right) {
//     test.setPosition(test.getPosition().x + 50, test.getPosition().y);
//     break;
//   } else if (event.key.code == sf::Keyboard::Left) {
//     test.setPosition(test.getPosition().x - 50, test.getPosition().y);
//     break;
//   } else if (event.key.code == sf::Keyboard::Up) {
//     test.setPosition(test.getPosition().x, test.getPosition().y - 50);
//     break;
//   } else if (event.key.code == sf::Keyboard::Down) {
//     test.setPosition(test.getPosition().x, test.getPosition().y + 50);
//     break;
//   }
// }