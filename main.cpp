#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "headers/board.h"

int main() {
  IShip* ship1_1 = new Ship1(Point(2, 2));
  IShip* ship1_2 = new Ship2(Point(3, 3));
  std::vector<IShip*> ships;
  int index = 0;
  ships.push_back(ship1_1);
  ships.push_back(ship1_2);
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
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
          ++index;  // нужно контролировать индекс(при нажатии каждого ентера увеличивается)
        }
        if (index < 2) {
          ships[index]->Move(event, board);
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